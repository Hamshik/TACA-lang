#include "../taca.hpp"
#include <iostream>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Verifier.h>
#include <llvm/Support/FileSystem.h>
#include <llvm/Support/raw_ostream.h>
#include <string>

extern "C" int codegen(ASTNode_t *root, const char *ll_path, char **ir_out) {
  LLVMContext ctx;
  Module mod("TQModule", ctx);
  IRBuilder<> b(ctx);

  /* Pass 1: collect/emit function bodies for all AST_FN nodes */
  std::function<void(ASTNode_t *)> walk;
  walk = [&](ASTNode_t *n) {
    if (!n)
      return;
    if (n->kind == AST_FN) {
      emit_function(n, mod, ctx);
      return;
    }
    if (n->kind == AST_SEQ) {
      walk(n->seq.a);
      walk(n->seq.b);
      return;
    }
  };
  emit_global(root, mod, ctx);
  walk(root);

  /* Emit top-level non-function statements into an init function */
  FunctionType *ftInit = FunctionType::get(Type::getVoidTy(ctx), false);
  Function *initFn =
      Function::Create(ftInit, Function::InternalLinkage, "init", mod);
  {
    BasicBlock *entry = BasicBlock::Create(ctx, "entry", initFn);
    IRBuilder<> ib(entry);
    IRBuilder<> entryB(entry, entry->begin());
    LocalMap locals;
    std::function<void(ASTNode_t *)> emit_nonfn = [&](ASTNode_t *n) {
      if (!n)
        return;
      if (n->kind == AST_FN)
        return;
      if (n->kind == AST_SEQ) {
        emit_nonfn(n->seq.a);
        emit_nonfn(n->seq.b);
        return;
      }
      emit_expr(n, ctx, ib, entryB, locals);
    };
    emit_nonfn(root);
    if (!entry->getTerminator())
      ib.CreateRetVoid();
  }

  /* ensure user main exists */
  Function *userMain = mod.getFunction("main");
  if (!userMain) {
    std::cerr << "No user main function found for codegen\n";
    return 1;
  }

  FunctionType *ftStub = FunctionType::get(Type::getVoidTy(ctx), false);
  Function *stub =
      Function::Create(ftStub, Function::ExternalLinkage, "entrypoint", mod);

  BasicBlock *entry = BasicBlock::Create(ctx, "entry", stub);
  b.SetInsertPoint(entry);

  IRBuilder<> entryBuilder(entry, entry->begin());

  b.CreateCall(initFn);

  Function *exitFn = get_exit(mod, ctx);

  // call main
  llvm::Value *retv = b.CreateCall(userMain);

  // prepare exit code
  llvm::Value *exitCode;
  if (userMain->getReturnType()->isVoidTy())
    exitCode = b.getInt32(0);
  else
    exitCode = b.CreateIntCast(retv, b.getInt32Ty(), true);

  // call exit(main())
  b.CreateCall(exitFn, {exitCode});
  b.CreateUnreachable();

  // verify
  std::string verr;
  raw_string_ostream verrs(verr);
  if (verifyModule(mod, &verrs)) {
    std::cerr << TACA_BOLD TACA_RED "LLVM verify error: " TACA_RESET << verrs.str() << std::endl;
    return 1;
  }

  // materialize IR to string
  std::string ir;
  raw_string_ostream irs(ir);
  mod.print(irs, nullptr);
  irs.flush();

  // optionally write to file
  if (ll_path) {
    std::error_code ec;
    raw_fd_ostream out(ll_path, ec, sys::fs::OF_Text);
    if (ec) {
      std::cerr << "Failed to open " << ll_path << ": " << ec.message()
                << std::endl;
      return 1;
    }
    out << ir;
    out.flush();
    std::cout << "LLVM IR written to " << ll_path << std::endl;
  }

  printf(TACA_BOLD TACA_GREEN
         "SUCCESS: Compilation succeeded with no errors or warnings\n" TACA_RESET);

  if (ir_out) {
    *ir_out = (char *)malloc(ir.size() + 1);
    if (!*ir_out)
      return 1;
    memcpy(*ir_out, ir.c_str(), ir.size() + 1);
  }
  return 0;
}
