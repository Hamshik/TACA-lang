#include "codegen/codegen.h"\n#include "ast/nodes.h"\n#include "ast/ast_enum.h" 
#include "codegen/codegen.h"\n#include "ast/nodes.h"\n#include "ast/ast_enum.h" 
#include <cstdio>
#include <string>

static size_t idx = 0;
static size_t list = 0;

Value *generateList(ASTNode_t *n, LLVMContext &ctx, IRBuilder<> &b,
                    IRBuilder<> &entryBuilder, LocalMap &locals) {
  Type *elemType = ir_type(n->sub_type, ctx);

  if (!elemType) {
    printf("Warning: invalid element type for list codegen at line %d, col %d\n",
           n->line, n->col);
    return nullptr;
  }
  
  ArrayType *arrayType = ArrayType::get(elemType, n->list.num);

  // Allocate using entryBuilder (Top of function)
  AllocaInst *arrayPtr =
      entryBuilder.CreateAlloca(arrayType, nullptr, n->list.target->var);

  ASTNode_t *curr = n->list.elements;
  uint32_t index = 0;

  while (curr) {
    ASTNode_t *exprNode = (curr->kind == AST_SEQ) ? curr->seq.a : curr;
    Value *elementVal = emit_expr(exprNode, ctx, b, entryBuilder, locals);

    // Use "b" (Current Block), NOT entryBuilder for logic!
    std::vector<Value *> indices = {b.getInt32(0), b.getInt32(index++)};
    Value *elementAddr = b.CreateGEP(arrayType, arrayPtr, indices);

    b.CreateStore(elementVal, elementAddr);

    if (curr->kind != AST_SEQ)
      break;
    curr = curr->seq.b;
  }

  // Map the variable name to our actual filled array
  locals[n->list.target->var] = arrayPtr;

  return arrayPtr;
}

Value *generateListElementPtr(ASTNode_t *n, LLVMContext &ctx, IRBuilder<> &b,
                              IRBuilder<> &entryBuilder, LocalMap &locals) {
  auto it = locals.find(n->index.target->var ? n->index.target->var : "");

  if (it == locals.end()) {
    printf("Warning: semaintic failed to catch 'the variable is not fond' "
           "error for list access at line %d, col %d\n",
           n->line, n->col);
    return nullptr;
  }

  llvm::AllocaInst *arrayPtr = llvm::dyn_cast<llvm::AllocaInst>(it->second);

  if (!arrayPtr) {
    printf("Warning: semaintic failed to catch 'the variable is not an array: "
           "arrayPtr' "
           "error for list access at line %d, col %d\n",
           n->line, n->col);
    return nullptr;
  }

  Value *indexVal = emit_expr(n->index.index, ctx, b, entryBuilder, locals);
  if (!indexVal)
    return nullptr;

  llvm::Type *elementType = ir_type(n->index.target->sub_type, ctx);
  if (!elementType) {
    printf("Warning: invalid element type for list access at line %d, col %d\n",
           n->line, n->col);
    return nullptr;
  }

  std::vector<Value *> indices = {b.getInt32(0), indexVal};
  (void)elementType;
  return b.CreateGEP(arrayPtr->getAllocatedType(), arrayPtr, indices);
}

Value *generateListAccess(ASTNode_t *n, LLVMContext &ctx, IRBuilder<> &b,
                          IRBuilder<> &entryBuilder, LocalMap &locals) {
  Value *elementAddr = generateListElementPtr(n, ctx, b, entryBuilder, locals);
  if (!elementAddr)
    return nullptr;

  llvm::Type *elementType = ir_type(n->index.target->sub_type, ctx);
  if (!elementType)
    return nullptr;

  return b.CreateLoad(elementType, elementAddr,
                      "load_tmp" + std::to_string(idx++));
}
