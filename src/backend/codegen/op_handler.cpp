#include "../../tarkiq.h"
#include "../../frontend/ast/ASTNode.h"
#include "codegen.h"
#include "llvm/IR/Value.h"
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>

llvm::Value *emit_binop(ASTNode_t *n, LLVMContext &ctx, IRBuilder<> &b,
                        IRBuilder<> &entryBuilder, LocalMap &locals) {
  llvm::Value *L = emit_expr(n->bin.left, ctx, b, entryBuilder, locals);
  llvm::Value *R = emit_expr(n->bin.right, ctx, b, entryBuilder, locals);
  if (!L || !R)
    return nullptr;

  if (is_float_dtype(n->datatype)) {
    switch (n->bin.op) {
    case OP_ADD:
      return b.CreateFAdd(L, R);
    case OP_SUB:
      return b.CreateFSub(L, R);
    case OP_MUL:
      return b.CreateFMul(L, R);
    case OP_DIV:
      return b.CreateFDiv(L, R);
    default:
      return nullptr;
    }
  }

  switch (n->bin.op) {
  case OP_ADD:
    return b.CreateAdd(L, R);
  case OP_SUB:
    return b.CreateSub(L, R);
  case OP_MUL:
    return b.CreateMul(L, R);
  case OP_DIV:
    return is_unsigned_dtype(n->datatype) ? b.CreateUDiv(L, R)
                                          : b.CreateSDiv(L, R);
  case OP_EQ:
    return b.CreateICmpEQ(L, R);
  case OP_NEQ:
    return b.CreateICmpNE(L, R);
  case OP_LT:
    return is_unsigned_dtype(n->datatype) ? b.CreateICmpULT(L, R)
                                          : b.CreateICmpSLT(L, R);
  case OP_LE:
    return is_unsigned_dtype(n->datatype) ? b.CreateICmpULE(L, R)
                                          : b.CreateICmpSLE(L, R);
  case OP_GT:
    return is_unsigned_dtype(n->datatype) ? b.CreateICmpUGT(L, R)
                                          : b.CreateICmpSGT(L, R);
  case OP_GE:
    return is_unsigned_dtype(n->datatype) ? b.CreateICmpUGE(L, R)
                                          : b.CreateICmpSGE(L, R);
  default:
    return nullptr;
  }
}

llvm::Value *emit_unop(ASTNode_t *n, LLVMContext &ctx, IRBuilder<> &b,
                       IRBuilder<> &entryBuilder, LocalMap &locals) {
  llvm::Value *opnd = emit_expr(n->unop.operand, ctx, b, entryBuilder, locals);
  if (!opnd)
    return nullptr;

  switch (n->unop.op) {
  case OP_NEG:
    return is_float_dtype(n->datatype) ? b.CreateFNeg(opnd) : b.CreateNeg(opnd);
  case OP_NOT:
    return b.CreateNot(opnd);
  default:
    return opnd;
  }
}

llvm::Value *emit_assing(ASTNode_t *n, LLVMContext &ctx, IRBuilder<> &b,
                         IRBuilder<> &entryBuilder, LocalMap &locals) {

  std::string name =
      n->assign.lhs && n->assign.lhs->var ? n->assign.lhs->var : "";
  DataTypes_t t = n->datatype != UNKNOWN
                      ? n->datatype
                      : (n->assign.lhs ? n->assign.lhs->datatype : UNKNOWN);

  if (t == UNKNOWN && n->assign.rhs)
    t = n->assign.rhs->datatype;
  AllocaInst *alloca = nullptr;
  Module *m = b.GetInsertBlock()->getModule();
  GlobalVariable *gv = nullptr;
  auto it = locals.find(name);

  if (it != locals.end()) {
    alloca = it->second;
  } else {
    gv = m->getGlobalVariable(name, true);
    if (!gv) {
      gv = new GlobalVariable(
          *m, ir_type(n->datatype, ctx),
          false,                                             // isConstant
          GlobalValue::ExternalLinkage,                      // linkage
          Constant::getNullValue(ir_type(n->datatype, ctx)), // initializer
          n->assign.lhs->var                                             // name
      );
    }
  }

  llvm::Value *rhs = emit_expr(n->assign.rhs, ctx, b, entryBuilder, locals);

  if (!rhs)
    return nullptr;
  if (alloca)
    b.CreateStore(rhs, alloca);
  else if (gv)
    b.CreateStore(rhs, gv);
  return rhs;
}

void emit_global(ASTNode_t *n, Module &mod, LLVMContext &ctx) {
    if (!n) return;
    if (n->kind == AST_SEQ) { emit_global(n->seq.a, mod, ctx); emit_global(n->seq.b, mod, ctx); return; }
    if (n->kind == AST_ASSIGN && n->assign.is_declaration) {
        std::string name = n->assign.lhs->var;
        DataTypes_t t = n->datatype != UNKNOWN ? n->datatype : n->assign.lhs->datatype;
        if (mod.getGlobalVariable(name)) return;
        new GlobalVariable(
            mod,
            ir_type(t, ctx),
            false,
            GlobalValue::ExternalLinkage,
            Constant::getNullValue(ir_type(t, ctx)),
            name
        );
    }
}