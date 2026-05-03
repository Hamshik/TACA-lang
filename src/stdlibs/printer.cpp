#include "codegen/codegen.h"
#include "ast/nodes.h"
#include "ast/ast_enum.h"
#include <string>

using namespace llvm;

llvm::Value *to_i64(llvm::Value *v, llvm::IRBuilder<> &b) {


  auto *i64 = llvm::Type::getInt64Ty(b.getContext());

  if (v->getType()->isIntegerTy())
    return b.CreateSExt(v, i64);

  if (v->getType()->isPointerTy())
    return b.CreatePtrToInt(v, i64);

  return v;
}

Function *get_printf(Module &m, LLVMContext &ctx) {
  if (Function *f = m.getFunction("printf"))
    return f;
  std::vector<Type *> params{PointerType::get(ctx, 0)};
  FunctionType *ft = FunctionType::get(Type::getInt32Ty(ctx), params, true);
  return Function::Create(ft, Function::ExternalLinkage, "printf", m);
}

Value *emit_print_like(const char *fmt, Value *v, LLVMContext &ctx,
                             IRBuilder<> &b) {
  Module *m = b.GetInsertBlock()->getModule();
  Function *printfFn = get_printf(*m, ctx);
  Value *fmtConst = b.CreateGlobalString(fmt, "fmt");
  std::vector<Value *> argv{fmtConst, v};
  return b.CreateCall(printfFn, argv);
}

Value *emit_println(ASTNode_t *argNode, Value *argV,
                          LLVMContext &ctx, IRBuilder<> &b) {

  Module *m = b.GetInsertBlock()->getModule();
  Function *printfFn = get_printf(*m, ctx);

  switch (argNode->datatype) {

    // ---------------- STRING ----------------
  case STRINGS: {
    llvm::Type *i8ptr = PointerType::getUnqual(Type::getInt8Ty(ctx));

    if (argV->getType() != i8ptr)
      argV = b.CreateBitCast(argV, i8ptr);

    Value *fmt = b.CreateGlobalStringPtr("%s\n");
    return b.CreateCall(printfFn, {fmt, argV});
  }

  // ---------------- CHARACTER → STRING ----------------
  case CHARACTER: {
    // create stack buffer: char[2] = {c, 0}
    // printf("char"); // debug

    Value *c = b.CreateTrunc(argV, Type::getInt8Ty(ctx));

    AllocaInst *buf = b.CreateAlloca(Type::getInt8Ty(ctx), nullptr, "charbuf");

    Value *zero = b.getInt32(0);
    Value *one = b.getInt32(1);

    // buf[0] = char
    Value *ptr0 = b.CreateGEP(Type::getInt8Ty(ctx), buf, zero);
    b.CreateStore(c, ptr0);

    // buf[1] = '\0'
    Value *ptr1 = b.CreateGEP(Type::getInt8Ty(ctx), buf, one);
    b.CreateStore(ConstantInt::get(Type::getInt8Ty(ctx), 0), ptr1);

    Value *fmt = b.CreateGlobalStringPtr("%s\n");
    return b.CreateCall(printfFn, {fmt, buf});
  }

    // ---------------- BOOL ----------------
  case BOOL: {
    Module *m = b.GetInsertBlock()->getModule();

    Value *cond = argV;

    Value *trueStr = b.CreateGlobalStringPtr("true\n");
    Value *falseStr = b.CreateGlobalStringPtr("false\n");

    Value *selected = b.CreateSelect(cond, trueStr, falseStr);

    return b.CreateCall(get_printf(*m, ctx), {selected});
  }

  // ---------------- FLOAT ----------------
  case F32:
  case F64:
  case F128: {
    Value *d = (argNode->datatype == F32)
                         ? b.CreateFPExt(argV, Type::getDoubleTy(ctx))
                         : argV;

    Value *fmt = b.CreateGlobalStringPtr("%f\n");
    return b.CreateCall(printfFn, {fmt, d});
  }

  // ---------------- INT ----------------
  default:
    if (argV->getType()->isPointerTy()) {
      // treat as string fallback
      Value *fmt = b.CreateGlobalStringPtr("%s\n");
      return b.CreateCall(printfFn, {fmt, argV});
    }

    Value *i = b.CreateSExtOrBitCast(argV, Type::getInt64Ty(ctx));
    Value *fmt = b.CreateGlobalStringPtr("%lld\n");

    return b.CreateCall(printfFn, {fmt, i});
  }
}

Value *emit_print(ASTNode_t *argNode, Value *argV, LLVMContext &ctx,
                        IRBuilder<> &b) {

  Module *m = b.GetInsertBlock()->getModule();
  Function *printfFn = get_printf(*m, ctx);

  switch (argNode->datatype) {

    // ---------------- STRING ----------------
  case STRINGS: {
    llvm::Type *i8ptr = PointerType::getUnqual(Type::getInt8Ty(ctx));

    if (argV->getType() != i8ptr)
      argV = b.CreateBitCast(argV, i8ptr);

    Value *fmt = b.CreateGlobalStringPtr("%s\n");
    return b.CreateCall(printfFn, {fmt, argV});
  }

  // ---------------- CHARACTER → STRING ----------------
  case CHARACTER: {
    // create stack buffer: char[2] = {c, 0}
    printf("char\n");
    Value *c = b.CreateTrunc(argV, Type::getInt8Ty(ctx));

    static size_t id = 0;

    AllocaInst *buf = b.CreateAlloca(Type::getInt8Ty(ctx), nullptr,
                                     "charbuf" + std::to_string(id++));

    Value *zero = b.getInt32(0);
    Value *one = b.getInt32(1);

    // buf[0] = char
    Value *ptr0 = b.CreateGEP(Type::getInt8Ty(ctx), buf, zero);
    b.CreateStore(c, ptr0);

    // buf[1] = '\0'
    Value *ptr1 = b.CreateGEP(Type::getInt8Ty(ctx), buf, one);
    b.CreateStore(ConstantInt::get(Type::getInt8Ty(ctx), 0), ptr1);

    Value *fmt = b.CreateGlobalStringPtr("%s");
    return b.CreateCall(printfFn, {fmt, buf});
  }

    // ---------------- BOOL ----------------
  case BOOL: {
    Module *m = b.GetInsertBlock()->getModule();

    Value *cond = argV;

    Value *trueStr = b.CreateGlobalStringPtr("true");
    Value *falseStr = b.CreateGlobalStringPtr("false");

    Value *selected = b.CreateSelect(cond, trueStr, falseStr);

    return b.CreateCall(get_printf(*m, ctx), {selected});
  }

  // ---------------- FLOAT ----------------
  case F32:
  case F64:
  case F128: {
    Value *d = (argNode->datatype == F32)
                         ? b.CreateFPExt(argV, Type::getDoubleTy(ctx))
                         : argV;

    Value *fmt = b.CreateGlobalStringPtr("%f\n");
    return b.CreateCall(printfFn, {fmt, d});
  }

    // ---------------- INT ----------------
  default: {
    if (argV->getType()->isPointerTy()) {
      // treat as string fallback
      Value *fmt = b.CreateGlobalStringPtr("%s");
      return b.CreateCall(printfFn, {fmt, argV});
    }

    Value *i = b.CreateSExtOrBitCast(argV, Type::getInt64Ty(ctx));
    Value *fmt = b.CreateGlobalStringPtr("%lld");

    return b.CreateCall(printfFn, {fmt, i});
  }
  }
}
