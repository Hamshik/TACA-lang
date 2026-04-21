#ifndef LIBS_H
#define LIBS_H

#ifdef __cplusplus
extern "C" {
#endif

// C-compatible declarations (if any) go here

#ifdef __cplusplus
}
#endif
#include "../taca.h"

#ifdef __cplusplus

#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/IRBuilder.h>   // ✅ REQUIRED

using namespace llvm;

Function* get_printf(Module &m, LLVMContext &ctx);

llvm::Value* emit_print_like(const char *fmt, llvm::Value *v, LLVMContext &ctx, IRBuilder<> &b);

llvm::Value* emit_println(ASTNode_t *argNode, llvm::Value *argV, LLVMContext &ctx, IRBuilder<> &b);

llvm::Value* print(ASTNode_t *n, argvec args, LLVMContext &ctx, IRBuilder<> &b);

Function *get_exit(Module &mod, LLVMContext &ctx);
#endif

#endif