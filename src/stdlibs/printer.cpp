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

llvm::Value *emit_println(ASTNode_t *argNode, llvm::Value *argV,
                          LLVMContext &ctx, IRBuilder<> &b) {
  // choose format by datatype
  switch (argNode->datatype) {
  case STRINGS:
    return emit_print_like("%s\n", argV, ctx, b);
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
    // Convert [N x i8]* -> i8*
    argV = b.CreateInBoundsGEP(argV->getType(), argV,
                               {b.getInt32(0), b.getInt32(0)}, "strptr");
    break;
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