#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include "../ast/ASTNode.h"
#include "stdlibs.h"

using namespace llvm;

Function* get_printf(Module &m, LLVMContext &ctx) {
    if (Function *f = m.getFunction("printf")) return f;
    std::vector<Type*> params{PointerType::get(ctx, 0)};
    FunctionType *ft = FunctionType::get(Type::getInt32Ty(ctx), params, true);
    return Function::Create(ft, Function::ExternalLinkage, "printf", m);
}

llvm::Value* emit_print_like(const char *fmt, llvm::Value *v, LLVMContext &ctx, IRBuilder<> &b) {
    Module *m = b.GetInsertBlock()->getModule();
    Function *printfFn = get_printf(*m, ctx);
    llvm::Value *fmtConst = b.CreateGlobalString(fmt, "fmt");
    std::vector<llvm::Value*> argv{fmtConst, v};
    return b.CreateCall(printfFn, argv);
}

llvm::Value* emit_println(ASTNode_t *argNode, llvm::Value *argV, LLVMContext &ctx, IRBuilder<> &b) {
    // choose format by datatype
    switch (argNode->datatype) {
        case STRINGS:
            return emit_print_like("%s\n", argV, ctx, b);
        case BOOL: {
            llvm::Value *i = b.CreateZExt(argV, Type::getInt32Ty(ctx));
            return emit_print_like("%d\n", i, ctx, b);
        }
        case F32: case F64: case F128: {
            llvm::Value *d = argNode->datatype == F32 ? b.CreateFPExt(argV, Type::getDoubleTy(ctx)) : argV;
            return emit_print_like("%f\n", d, ctx, b);
        }
        default: {
            // integers -> extend to i64, unsigned treated same for now
            llvm::Value *i = b.CreateSExtOrBitCast(argV, Type::getInt64Ty(ctx));
            return emit_print_like("%lld\n", i, ctx, b);
        }
    }
}