#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/IRBuilder.h>
#include "codegen.h"
#include "../ast/ASTNode.h"
#include "../stdlibs/stdlibs.h"
#include "llvm/IR/Value.h"

Function* get_or_create_prototype(ASTNode_t *fn_ast, Module &mod, LLVMContext &ctx) {
    std::vector<Type*> params;
    for (int i = 0; i < fn_ast->fn_def.param_count; ++i) {
        params.push_back(ir_type(fn_ast->fn_def.params[i].type, ctx));
    }
    Type *retTy = ir_type(fn_ast->fn_def.ret, ctx);
    if (retTy->isVoidTy() && fn_ast->fn_def.ret == UNKNOWN) retTy = Type::getInt32Ty(ctx);
    FunctionType *ft = FunctionType::get(retTy, params, false);
    Function *fn = mod.getFunction(fn_ast->fn_def.name);
    if (!fn) {
        fn = Function::Create(ft, Function::ExternalLinkage, fn_ast->fn_def.name, mod);
    }
    return fn;
}

void emit_function(ASTNode_t *fn_ast, Module &mod, LLVMContext &ctx) {
    Function *fn = get_or_create_prototype(fn_ast, mod, ctx);
    if (!fn) return;
    BasicBlock *entry = BasicBlock::Create(ctx, "entry", fn);
    IRBuilder<> b(entry);
    IRBuilder<> entryBuilder(entry, entry->begin());
    LocalMap locals;

    // map params
    unsigned idx = 0;
    for (auto &arg : fn->args()) {
        const char *pname = fn_ast->fn_def.params[idx].name;
        arg.setName(pname);
        AllocaInst *alloca = get_or_create_alloca(pname, fn_ast->fn_def.params[idx].type, ctx, entryBuilder, locals);
        b.CreateStore(&arg, alloca);
        ++idx;
    }

    emit_expr(fn_ast->fn_def.body, ctx, b, entryBuilder, locals);
    if (!entry->getTerminator()) {
        if (fn->getReturnType()->isVoidTy())
            b.CreateRetVoid();
        else
            b.CreateRet(ConstantInt::get(fn->getReturnType(), 0));
    }
}

llvm::Value* emit_call(ASTNode_t *n, LLVMContext &ctx, IRBuilder<> &b,
                       IRBuilder<> &entryBuilder, LocalMap &locals) {

    std::vector<llvm::Value*> args;

    // Evaluate arguments
    for (ASTNode_t *it = n->call.args; it;) {
        ASTNode_t *cur = (it->kind == AST_SEQ) ? it->seq.a : it;
        if (cur) {
            llvm::Value *v = emit_expr(cur, ctx, b, entryBuilder, locals);
            if (!v)
                v = ConstantInt::get(Type::getInt32Ty(ctx), 0);
            args.push_back(v);
        }
        it = (it->kind == AST_SEQ) ? it->seq.b : nullptr;
    }

    bool isPrint = !strcmp(n->call.name, "print") || !strcmp(n->call.name, "println");

    if (isPrint) {
        llvm::Value* argV = args.empty() ? 
            b.CreateGlobalString("", "emptystr") : args[0];

        ASTNode_t *argNode = args.empty() ? n : 
            ((n->call.args && n->call.args->kind == AST_SEQ) ? n->call.args->seq.a : n->call.args);

        Module *m = b.GetInsertBlock()->getModule();
        Function *printfFn = get_printf(*m, ctx);

        llvm::Value* fmt = nullptr;

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
            llvm::Value* nl = b.CreateGlobalString("\n", "newline");
            nl = b.CreateInBoundsGEP(nl->getType(), nl, {b.getInt32(0), b.getInt32(0)}, "nlptr");
            std::vector<llvm::Value*> printArgs = {fmt, argV};
            b.CreateCall(printfFn, printArgs);
            b.CreateCall(printfFn, nl); // print newline separately
            return nullptr;
        }

        // Normal print
        std::vector<llvm::Value*> printArgs = {fmt, argV};
        return b.CreateCall(printfFn, printArgs);
    }

    // Normal function call
    Module *m = b.GetInsertBlock()->getModule();
    const char *fname = n->call.name;

    if (!fname || strlen(fname) == 0) {
        fprintf(stderr, "ERROR: function call with empty name\n");
        exit(1);
    }

    Function *callee = m->getFunction(fname);
    if (!callee) {
        FunctionType *ft = FunctionType::get(b.getInt32Ty(), {}, true);
        callee = Function::Create(ft, Function::ExternalLinkage, fname, m);
    }

    return b.CreateCall(callee, args);
}