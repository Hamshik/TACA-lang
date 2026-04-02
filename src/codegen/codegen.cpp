#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Verifier.h>
#include <llvm/Support/FileSystem.h>
#include <llvm/Support/raw_ostream.h>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include "../ast/ASTNode.h"
#include "codegen.h"
#include "../utils/error_handler/error_msg.h"
#include "../eval/eval.h" /* for tq_parse_* */

using namespace llvm;
/* Minimal IR codegen:
 * - builds a module
 * - emits i32 @tq_main() that walks a tiny subset of the AST (numbers, +,-,*,/) and drops the result
 * - writes IR to out.ll
 */

static bool is_unsigned_dtype(DataTypes_t t) {
    switch (t) {
        case U8: case U16: case U32: case U64: case U128:
        case UF32: case UF64: case UF128:
            return true;
        default:
            return false;
    }
}

static Type* llvm_type_for(DataTypes_t t, LLVMContext &ctx) {
    switch (t) {
        case I8:  case U8:   return Type::getInt8Ty(ctx);
        case I16: case U16:  return Type::getInt16Ty(ctx);
        case I32: case U32:  return Type::getInt32Ty(ctx);
        case I64: case U64:  return Type::getInt64Ty(ctx);
        case I128:case U128: return IntegerType::get(ctx, 128);
        case F32: case UF32: return Type::getFloatTy(ctx);
        case F64: case UF64: return Type::getDoubleTy(ctx);
        case F128:case UF128:return Type::getFP128Ty(ctx);
        case BOOL:           return Type::getInt1Ty(ctx);
        case CHARACTER:      return Type::getInt8Ty(ctx);
        default:             return Type::getInt32Ty(ctx);
    }
}

static llvm::Value* emit_expr(ASTNode_t *n, LLVMContext &ctx, IRBuilder<> &b) {
    if (!n) return nullptr;
    switch (n->kind) {
        case AST_NUM:
            switch (n->datatype) {
                case I8:
                    return ConstantInt::get(Type::getInt8Ty(ctx),  strtoll(n->literal.raw, NULL, 0), true);
                case I16:
                    return ConstantInt::get(Type::getInt16Ty(ctx), strtoll(n->literal.raw, NULL, 0), true);
                case I32:
                    return ConstantInt::get(Type::getInt32Ty(ctx), strtoll(n->literal.raw, NULL, 0), true);
                case I64:
                    return ConstantInt::get(Type::getInt64Ty(ctx), strtoll(n->literal.raw, NULL, 0), true);
                case I128: {
                    int ok = 0;
                    __int128 v = tq_parse_i128(n->literal.raw, &ok);
                    if (!ok) {
                        panic(&file, n->line, n->col, n->pos, RT_NUM_LITERAL_UNSUPPORTED, NULL);
                        return nullptr;
                    }
                    uint64_t words[2];
                    unsigned __int128 uv = (v < 0) ? (unsigned __int128)(-v) : (unsigned __int128)v;
                    words[0] = (uint64_t)uv;
                    words[1] = (uint64_t)(uv >> 64);
                    APInt api(128, ArrayRef<uint64_t>(words, 2));
                    if (v < 0) api = api.sext(128);
                    return ConstantInt::get(IntegerType::get(ctx, 128), api);
                }
                case U8:
                    return ConstantInt::get(Type::getInt8Ty(ctx),  strtoull(n->literal.raw, NULL, 0), false);
                case U16:
                    return ConstantInt::get(Type::getInt16Ty(ctx), strtoull(n->literal.raw, NULL, 0), false);
                case U32:
                    return ConstantInt::get(Type::getInt32Ty(ctx), strtoull(n->literal.raw, NULL, 0), false);
                case U64:
                    return ConstantInt::get(Type::getInt64Ty(ctx), strtoull(n->literal.raw, NULL, 0), false);
                case U128: {
                    int ok = 0;
                    unsigned __int128 v = tq_parse_u128(n->literal.raw, &ok);
                    if (!ok) {
                        panic(&file, n->line, n->col, n->pos, RT_NUM_LITERAL_UNSUPPORTED, NULL);
                        return nullptr;
                    }
                    uint64_t words[2];
                    words[0] = (uint64_t)v;
                    words[1] = (uint64_t)(v >> 64);
                    APInt api(128, ArrayRef<uint64_t>(words, 2));
                    return ConstantInt::get(IntegerType::get(ctx, 128), api);
                }
                case F32:
                    return ConstantFP::get(Type::getFloatTy(ctx),  strtof(n->literal.raw, NULL));
                case F64:
                    return ConstantFP::get(Type::getDoubleTy(ctx), strtod(n->literal.raw, NULL));
                case F128:
                    return ConstantFP::get(Type::getFP128Ty(ctx),  strtold(n->literal.raw, NULL));
                case UF32:
                    return ConstantFP::get(Type::getFloatTy(ctx),  strtof(n->literal.raw, NULL));
                case UF64:
                    return ConstantFP::get(Type::getDoubleTy(ctx), strtod(n->literal.raw, NULL));
                case UF128:
                    return ConstantFP::get(Type::getFP128Ty(ctx),  strtold(n->literal.raw, NULL));
                default:
                    panic(&file, n->line, n->col, n->pos, RT_NUM_LITERAL_UNSUPPORTED, NULL);
                    return nullptr;
            }
        case AST_BINOP: {
            llvm::Value *L = emit_expr(n->bin.left, ctx, b);
            llvm::Value *R = emit_expr(n->bin.right, ctx, b);
            if (!L || !R) return nullptr;
            switch (n->bin.op) {
                case OP_ADD: return b.CreateAdd(L, R);
                case OP_SUB: return b.CreateSub(L, R);
                case OP_MUL: return b.CreateMul(L, R);
                case OP_DIV: return is_unsigned_dtype(n->datatype) ? b.CreateUDiv(L, R) : b.CreateSDiv(L, R);
                case OP_EQ:  return b.CreateICmpEQ(L, R);
                case OP_NEQ: return b.CreateICmpNE(L, R);
                case OP_LT:  return is_unsigned_dtype(n->datatype) ? b.CreateICmpULT(L, R) : b.CreateICmpSLT(L, R);
                case OP_LE:  return is_unsigned_dtype(n->datatype) ? b.CreateICmpULE(L, R) : b.CreateICmpSLE(L, R);
                case OP_GT:  return is_unsigned_dtype(n->datatype) ? b.CreateICmpUGT(L, R) : b.CreateICmpSGT(L, R);
                case OP_GE:  return is_unsigned_dtype(n->datatype) ? b.CreateICmpUGE(L, R) : b.CreateICmpSGE(L, R);
                default: return nullptr;
            }
        }
        case AST_SEQ:
            emit_expr(n->seq.a, ctx, b);
            return emit_expr(n->seq.b, ctx, b);
        case AST_STR: {
            return b.CreateGlobalString(n->literal.raw ? n->literal.raw : "", "strlit");
        }
        case AST_BOOL:
            return ConstantInt::get(Type::getInt1Ty(ctx), n->datatype == BOOL ? 1 : 0);
        default:
            return nullptr;
    }
}

extern "C" int codegen(ASTNode_t* root) {
    LLVMContext ctx;
    Module mod("tarkiq_module", ctx);
    IRBuilder<> b(ctx);

    // define i32 @tq_main()
    FunctionType *ft = FunctionType::get(b.getInt32Ty(), false);
    Function *fn = Function::Create(ft, Function::ExternalLinkage, "tq_main", mod);
    BasicBlock *entry = BasicBlock::Create(ctx, "entry", fn);
    b.SetInsertPoint(entry);

    // Emit whole AST (currently expressions only; statements ignored but walked).
    emit_expr(root, ctx, b);
    // Return 0 for now.
    b.CreateRet(b.getInt32(0));

    // verify
    std::string verr;
    raw_string_ostream verrs(verr);
    if (verifyModule(mod, &verrs)) {
        std::cerr << "LLVM verify error: " << verrs.str() << std::endl;
        return 1;
    }

    // write IR
    std::error_code ec;
    raw_fd_ostream out("out.ll", ec, sys::fs::OF_Text);
    if (ec) {
        std::cerr << "Failed to open out.ll: " << ec.message() << std::endl;
        return 1;
    }
    mod.print(out, nullptr);
    out.flush();
    std::cout << "LLVM IR written to out.ll" << std::endl;
    return 0;
}
