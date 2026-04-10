#include "tarkiq.h"
#include "../ast/ASTNode.h"
#include "stdlibs.h"
#include "llvm/IR/IRBuilder.h"
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include "../codegen/codegen.h"

using namespace llvm;

Function* get_printf(Module &m, LLVMContext &ctx) {
    if (Function *f = m.getFunction("printf")) return f;
    std::vector<Type*> params{PointerType::get(ctx, 0)};
    FunctionType *ft = FunctionType::get(Type::getInt32Ty(ctx), params, true);
    return Function::Create(ft, Function::ExternalLinkage, "printf", m);
}

llvm::Value *emit_print_like(const char *fmt, llvm::Value *v, LLVMContext &ctx,
                             IRBuilder<> &b) {
  Module *m = b.GetInsertBlock()->getModule();
  Function *printfFn = get_printf(*m, ctx);
  llvm::Value *fmtConst = b.CreateGlobalString(fmt, "fmt");
  std::vector<llvm::Value *> argv{fmtConst, v};
  return b.CreateCall(printfFn, argv);
}

/* Internal helper added to the generated module to print a codepoint as UTF-8
 * without relying on locale/%lc. */
static Function *get_or_create_tq_print_cp(Module *m, LLVMContext &ctx) {
    if (Function *f = m->getFunction("tq_print_cp")) return f;

    Type *i1  = Type::getInt1Ty(ctx);
    Type *i8  = Type::getInt8Ty(ctx);
    Type *i32 = Type::getInt32Ty(ctx);

    FunctionType *ft = FunctionType::get(Type::getVoidTy(ctx), {i32, i1}, false);
    Function *f = Function::Create(ft, Function::InternalLinkage, "tq_print_cp", m);

    BasicBlock *entry = BasicBlock::Create(ctx, "entry", f);
    BasicBlock *one   = BasicBlock::Create(ctx, "one", f);
    BasicBlock *two   = BasicBlock::Create(ctx, "two", f);
    BasicBlock *twoDo = BasicBlock::Create(ctx, "two.do", f);
    BasicBlock *three = BasicBlock::Create(ctx, "three", f);
    BasicBlock *threeDo = BasicBlock::Create(ctx, "three.do", f);
    BasicBlock *four  = BasicBlock::Create(ctx, "four", f);
    BasicBlock *done  = BasicBlock::Create(ctx, "done", f);

    IRBuilder<> b(entry);
    auto args = f->arg_begin();
    Value *cp = args++;
    cp->setName("cp");
    Value *nl = args;
    nl->setName("nl");

    Function *putcharF = cast<Function>(m->getOrInsertFunction(
        "putchar", FunctionType::get(i32, {i32}, false)).getCallee());
    auto emit_byte = [&](IRBuilder<> &ib, Value *byte32) {
        Value *b8 = ib.CreateTrunc(byte32, i8);
        Value *b32 = ib.CreateZExt(b8, i32);
        ib.CreateCall(putcharF, {b32});
    };

    Value *is1 = b.CreateICmpULE(cp, b.getInt32(0x7F));
    b.CreateCondBr(is1, one, two);

    // 1 byte
    b.SetInsertPoint(one);
    emit_byte(b, cp);
    b.CreateBr(done);

    // 2-byte decision
    b.SetInsertPoint(two);
    Value *is2 = b.CreateICmpULE(cp, b.getInt32(0x7FF));
    b.CreateCondBr(is2, twoDo, three);

    b.SetInsertPoint(twoDo);
    {
        Value *b1 = b.CreateOr(b.getInt32(0xC0), b.CreateLShr(cp, 6));
        Value *b2 = b.CreateOr(b.getInt32(0x80), b.CreateAnd(cp, b.getInt32(0x3F)));
        emit_byte(b, b1);
        emit_byte(b, b2);
        b.CreateBr(done);
    }

    // 3-byte decision
    b.SetInsertPoint(three);
    Value *is3 = b.CreateICmpULE(cp, b.getInt32(0xFFFF));
    b.CreateCondBr(is3, threeDo, four);

    b.SetInsertPoint(threeDo);
    {
        Value *b1 = b.CreateOr(b.getInt32(0xE0), b.CreateLShr(cp, 12));
        Value *b2 = b.CreateOr(b.getInt32(0x80), b.CreateAnd(b.CreateLShr(cp, 6), b.getInt32(0x3F)));
        Value *b3 = b.CreateOr(b.getInt32(0x80), b.CreateAnd(cp, b.getInt32(0x3F)));
        emit_byte(b, b1);
        emit_byte(b, b2);
        emit_byte(b, b3);
        b.CreateBr(done);
    }

    // 4-byte
    b.SetInsertPoint(four);
    {
        Value *b1 = b.CreateOr(b.getInt32(0xF0), b.CreateLShr(cp, 18));
        Value *b2 = b.CreateOr(b.getInt32(0x80), b.CreateAnd(b.CreateLShr(cp, 12), b.getInt32(0x3F)));
        Value *b3 = b.CreateOr(b.getInt32(0x80), b.CreateAnd(b.CreateLShr(cp, 6), b.getInt32(0x3F)));
        Value *b4 = b.CreateOr(b.getInt32(0x80), b.CreateAnd(cp, b.getInt32(0x3F)));
        emit_byte(b, b1);
        emit_byte(b, b2);
        emit_byte(b, b3);
        emit_byte(b, b4);
        b.CreateBr(done);
    }

    b.SetInsertPoint(done);
    BasicBlock *retbb = BasicBlock::Create(ctx, "ret", f);
    b.CreateCondBr(nl, retbb, retbb);
    b.SetInsertPoint(retbb);
    b.CreateRetVoid();

    return f;
}

llvm::Value *emit_println(ASTNode_t *argNode, llvm::Value *argV,
                          LLVMContext &ctx, IRBuilder<> &b) {
  // choose format by datatype
  switch (argNode->datatype) {
  case STRINGS:
    {
      Type *i8ptr = PointerType::get(ctx, 0);
      if (argV->getType() != i8ptr) {
        argV = b.CreatePointerCast(argV, i8ptr);
      }
    }
    return emit_print_like("%s\n", argV, ctx, b);
  case CHARACTER: {
    llvm::Value *cp = b.CreateSExtOrBitCast(argV, Type::getInt32Ty(ctx));
    Module *m = b.GetInsertBlock()->getModule();
    Function *helper = get_or_create_tq_print_cp(m, ctx);
    b.CreateCall(helper, {cp, b.getInt1(true)});
    return nullptr;
  }
  case BOOL: {
    llvm::Value *i = b.CreateZExt(argV, Type::getInt32Ty(ctx));
    return emit_print_like("%d\n", i, ctx, b);
  }
  case F32:
  case F64:
  case F128: {
    llvm::Value *d = argNode->datatype == F32
                         ? b.CreateFPExt(argV, Type::getDoubleTy(ctx))
                         : argV;
    return emit_print_like("%f\n", d, ctx, b);
  }
  default: {
    // integers -> extend to i64, unsigned treated same for now
    llvm::Value *i = b.CreateSExtOrBitCast(argV, Type::getInt64Ty(ctx));
    return emit_print_like("%lld\n", i, ctx, b);
  }
  }
}

llvm::Value* print(ASTNode_t *n, argvec args, LLVMContext &ctx, IRBuilder<> &b) {

  llvm::Value *argV =
      args.empty() ? b.CreateGlobalString("", "emptystr") : args[0];

  ASTNode_t *argNode = args.empty()
                           ? n
                           : ((n->call.args && n->call.args->kind == AST_SEQ)
                                  ? n->call.args->seq.a
                                  : n->call.args);

  Module *m = b.GetInsertBlock()->getModule();
  Function *printfFn = get_printf(*m, ctx);

  llvm::Value *fmt = nullptr;

  switch (argNode ? argNode->datatype : STRINGS) {
  case STRINGS:
    fmt = b.CreateGlobalString("%s", "fmt");
    {
      Type *i8ptr = PointerType::get(ctx, 0);
      if (argV->getType() != i8ptr) {
        argV = b.CreatePointerCast(argV, i8ptr);
      }
    }
    break;
  case CHARACTER:
    {
      llvm::Value *cp = b.CreateSExtOrBitCast(argV, Type::getInt32Ty(ctx));
      Module *m2 = b.GetInsertBlock()->getModule();
      Function *helper2 = get_or_create_tq_print_cp(m2, ctx);
      b.CreateCall(helper2, {cp, b.getInt1(false)});
      return nullptr;
    }
  case BOOL:
    fmt = b.CreateGlobalString("%d", "fmt");
    if (!argV->getType()->isIntegerTy(32))
      argV = b.CreateZExt(argV, Type::getInt32Ty(ctx));
    break;
  case F32:
  case F64:
  case F128:
    fmt = b.CreateGlobalString("%f", "fmt");
    if (argNode->datatype == F32)
      argV = b.CreateFPExt(argV, Type::getDoubleTy(ctx));
    break;
  default: // integers
    fmt = b.CreateGlobalString("%lld", "fmt");
    if (!argV->getType()->isIntegerTy(64))
      argV = b.CreateSExtOrBitCast(argV, Type::getInt64Ty(ctx));
    break;
  }

  // Add newline for println
  if (!strcmp(n->call.name, "println")) {
    llvm::Value *nl = b.CreateGlobalString("\n", "newline");
    nl = b.CreateInBoundsGEP(nl->getType(), nl, {b.getInt32(0), b.getInt32(0)},
                             "nlptr");
    std::vector<llvm::Value *> printArgs = {fmt, argV};
    b.CreateCall(printfFn, printArgs);
    b.CreateCall(printfFn, nl); // print newline separately
    return nullptr;
  }

  // Normal print
  std::vector<llvm::Value *> printArgs = {fmt, argV};
  return b.CreateCall(printfFn, printArgs);
}
