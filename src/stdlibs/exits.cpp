#include "../taca.h"


Function *get_exit(Module &mod, LLVMContext &ctx) {
    Function *exitFn = mod.getFunction("exit");
    if (!exitFn) {
        FunctionType *ft = FunctionType::get(
            Type::getVoidTy(ctx),                 // return void
            {Type::getInt32Ty(ctx)},             // takes int
            false
        );

        exitFn = Function::Create(
            ft,
            Function::ExternalLinkage,
            "exit",
            mod
        );
    }
    return exitFn;
}