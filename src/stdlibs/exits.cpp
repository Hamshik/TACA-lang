#include "codegen/codegen.h"

llvm::Function *get_exit(llvm::Module &mod, llvm::LLVMContext &ctx) {
  llvm::Function *exitFn = mod.getFunction("exit");
  if (!exitFn) {
    llvm::FunctionType *ft = llvm::FunctionType::get(llvm::Type::getVoidTy(ctx),
                                         {llvm::Type::getInt32Ty(ctx)},
                                         false);

    exitFn = llvm::Function::Create(ft, llvm::Function::ExternalLinkage, "exit", mod);
  }
  return exitFn;
}

llvm::Value *get_exit(llvm::Module *m, llvm::LLVMContext &ctx , std::vector<llvm::Value *> args, llvm::IRBuilder<> &b){
    llvm::Function *callee = m->getFunction("exit");

    // ensure exactly 1 argument
    llvm::Value *exitCode =
        args.empty() ? llvm::ConstantInt::get(llvm::Type::getInt32Ty(ctx), 0) : args[0];

    // cast to i32 if needed
    if (exitCode->getType() != llvm::Type::getInt32Ty(ctx)) {
      exitCode = b.CreateIntCast(exitCode, llvm::Type::getInt32Ty(ctx), true);
    }

    // create prototype if not exists
    if (!callee) {
      llvm::FunctionType *ft = llvm::FunctionType::get(llvm::Type::getVoidTy(ctx),
                                           {llvm::Type::getInt32Ty(ctx)},
                                           false);
      callee = llvm::Function::Create(ft, llvm::Function::ExternalLinkage, "exit", *m);
    }

    // emit call
    b.CreateCall(callee, {exitCode});

    // terminate block
    b.CreateUnreachable();

    return nullptr;
}

