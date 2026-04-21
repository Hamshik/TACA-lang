#include "../taca.h"

#include "llvm/IR/Constants.h"
#include "llvm/IR/Value.h"
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>

Function *get_or_create_prototype(ASTNode_t *fn_ast, Module &mod,
                                  LLVMContext &ctx) {
  std::vector<Type *> params;
  for (int i = 0; i < fn_ast->fn_def.param_count; ++i) {
    params.push_back(ir_type(fn_ast->fn_def.params[i].type, ctx));
  }
  Type *retTy = ir_type(fn_ast->fn_def.ret, ctx);
  if (retTy->isVoidTy() && fn_ast->fn_def.ret == UNKNOWN)
    retTy = Type::getInt32Ty(ctx);
  FunctionType *ft = FunctionType::get(retTy, params, false);
  Function *fn = mod.getFunction(fn_ast->fn_def.name);
  if (!fn) {
    fn = Function::Create(ft, Function::ExternalLinkage, fn_ast->fn_def.name,
                          mod);
  }
  return fn;
}

void emit_function(ASTNode_t *fn_ast, Module &mod, LLVMContext &ctx) {
  Function *fn = get_or_create_prototype(fn_ast, mod, ctx);
  if (!fn)
    return;
  BasicBlock *entry = BasicBlock::Create(ctx, "entry", fn);
  IRBuilder<> b(entry);
  IRBuilder<> entryBuilder(entry, entry->begin());
  LocalMap locals;

  // map params
  unsigned idx = 0;
  for (auto &arg : fn->args()) {
    const char *pname = fn_ast->fn_def.params[idx].name;
    arg.setName(pname);
    AllocaInst *alloca = get_or_create_alloca(
        pname, fn_ast->fn_def.params[idx].type, ctx, entryBuilder, locals);
    b.CreateStore(&arg, alloca);
    ++idx;
  }

  emit_expr(fn_ast->fn_def.body, ctx, b, entryBuilder, locals);
  if (!blockTerminated(b)) {
    if (fn->getReturnType()->isVoidTy()) 
      b.CreateRetVoid();
    else if(strcmp(fn_ast->fn_def.name, "main") == 0)
      b.CreateRet(ConstantInt::get(Type::getInt32Ty(ctx), 0));
    else 
      error(&file, fn_ast->line, fn_ast->col, fn_ast->pos, RET_NOT_DECLARED, fn_ast->fn_def.name);
  }
}

llvm::Value *emit_call(ASTNode_t *n, LLVMContext &ctx,
                       IRBuilder<> &b, IRBuilder<> &entryBuilder,
                       LocalMap &locals) {

  argvec args;

  // 🔹 Evaluate arguments
  for (ASTNode_t *it = n->call.args; it;) {
    ASTNode_t *cur = (it->kind == AST_SEQ) ? it->seq.a : it;

    if (cur) {
      llvm::Value *v = emit_expr(cur, ctx, b, entryBuilder, locals);
      if (!v)
        v = ConstantInt::get(Type::getInt32Ty(ctx), 0);
      args.push_back(v);
    }

    it = (it->kind == AST_SEQ) ? it->seq.b : nullptr;
  }

  Module *m = b.GetInsertBlock()->getModule();
  const char *fname = n->call.name;

  if (!fname || strlen(fname) == 0) {
    syserr("ERROR: function call with empty name\n");
  }

  bool isPrint = strcmp(fname, "print") == 0 ||
                 strcmp(fname, "println") == 0;

  bool isExit = strcmp(fname, "hlt") == 0;

  // 🔹 PRINT
  if (isPrint)
    return print(n, args, ctx, b);

  // 🔥 EXIT (hlt)
  if (isExit) {
    Function *callee = m->getFunction("exit");

    // ensure exactly 1 argument
    llvm::Value *exitCode = args.empty()
        ? ConstantInt::get(Type::getInt32Ty(ctx), 0)
        : args[0];

    // cast to i32 if needed
    if (exitCode->getType() != Type::getInt32Ty(ctx)) {
      exitCode = b.CreateIntCast(exitCode, Type::getInt32Ty(ctx), true);
    }

    // create prototype if not exists
    if (!callee) {
      FunctionType *ft = FunctionType::get(
          Type::getVoidTy(ctx),                 // void
          {Type::getInt32Ty(ctx)},              // (i32)
          false
      );
      callee = Function::Create(ft, Function::ExternalLinkage, "exit", m);
    }

    // emit call
    b.CreateCall(callee, {exitCode});

    // 🚨 terminate block
    b.CreateUnreachable();

    return nullptr;
  }

  // 🔹 NORMAL FUNCTION CALL
  Function *callee = m->getFunction(fname);

  if (!callee) {
    FunctionType *ft = FunctionType::get(b.getInt32Ty(), {}, true);
    callee = Function::Create(ft, Function::ExternalLinkage, fname, m);
  }

  return b.CreateCall(callee, args);
}