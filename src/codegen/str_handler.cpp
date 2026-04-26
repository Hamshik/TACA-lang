#include "../taca.hpp"
#include "SymbolTable/SymbolTable.hpp"
#include <cstring>
#include <llvm-22/llvm/IR/Module.h>
#include <stdint.h>
#include <stdlib.h>

uint32_t decode_utf8(const char *raw, size_t raw_len, size_t *byte_len,
                     Utf8Error *error) {
  if (!raw || raw_len == 0) {
    *error = Utf8Error::Empty;
    return 0;
  }

  const char *it = raw;
  const char *end = raw + raw_len;

  // 1. Validation check (since we can't use exceptions)
  if (utf8::find_invalid(it, end) != end) {
    *error = Utf8Error::InvalidUtf8;
    return 0;
  }

  // 2. Decode the first character (unchecked assumes prior validation)
  uint32_t cp = utf8::unchecked::next(it);
  *byte_len = (size_t)(it - raw);

  // 3. Safety Net: If it's not the end of the string, it's a multi-char literal
  if (it != end) {
    *error = Utf8Error::MultiCharacter;
    return 0;
  }

  *error = Utf8Error::None;
  return cp;
}

llvm::Value *to_i8_ptr(llvm::Value *v, IRBuilder<> &b) {
  auto &ctx = b.getContext();

  auto *i8Ty = llvm::Type::getInt8Ty(ctx);
  auto *i8Ptr = llvm::PointerType::getUnqual(i8Ty);

  // already correct type
  if (v->getType() == i8Ptr)
    return v;

  // global string: [N x i8]*
  if (auto *GV = llvm::dyn_cast<llvm::GlobalVariable>(v)) {
    auto *valTy = GV->getValueType();

    if (valTy->isArrayTy() && valTy->getArrayElementType() == i8Ty) {

      auto zero = llvm::ConstantInt::get(llvm::Type::getInt32Ty(ctx), 0);

      return b.CreateInBoundsGEP(valTy, GV, {zero, zero});
    }
  }

  // ⚠️ IMPORTANT: DO NOT silently pass wrong types
  llvm::errs() << "Invalid string conversion type: ";
  v->getType()->print(llvm::errs());
  llvm::errs() << "\n";

  return v;
}

Value *emit_char_to_string(Value *ch, LLVMContext &ctx, IRBuilder<> &b) {
  // allocate 2 bytes: char + null
  auto *i8Ty = Type::getInt8Ty(ctx);
  auto *i8Ptr = PointerType::getUnqual(Type::getInt8Ty(ctx));
  auto *i32Ty = Type::getInt32Ty(ctx);

  auto m = b.GetInsertBlock()->getModule();

  Function *mallocFn = m->getFunction("malloc");

  if (!mallocFn) {
    LLVMContext &ctx = m->getContext();

    Type *i8Ptr = PointerType::getUnqual(Type::getInt8Ty(ctx));
    Type *i64 = Type::getInt64Ty(ctx);

    FunctionType *mallocTy = FunctionType::get(i8Ptr, {i64}, false);

    mallocFn =
        Function::Create(mallocTy, Function::ExternalLinkage, "malloc", m);
  }

  Value *mem = b.CreateCall(mallocFn, ConstantInt::get(i32Ty, 2));

  Value *c8 = b.CreateTrunc(ch, i8Ty);

  b.CreateStore(c8, mem);
  Value *zeroPtr = b.CreateGEP(i8Ty, mem, b.getInt32(1));
  b.CreateStore(ConstantInt::get(i8Ty, 0), zeroPtr);

  return mem;
}