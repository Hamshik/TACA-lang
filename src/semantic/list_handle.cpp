#include "SymbolTable/SymbolTableInternal.hpp"
#include "taca.hpp"

extern "C" DataTypes_t list_handle(ASTNode_t *n, DataTypes_t type) {
  ASTNode_t *curr = n->list.elements;
  size_t count = 0;

  if(!n->list.target)
    syserr("target is null in list_handle");

  while (curr && (curr->kind == AST_SEQ || curr->kind == AST_BINOP ||
                  curr->kind == AST_UNOP)) {

    if (curr->kind == AST_SEQ) {
      check_expr(curr->seq.a, n->datatype);
      curr = curr->seq.b;
    } else if (curr->kind == AST_BINOP) {
      check_expr(curr->bin.left, n->datatype);
      check_expr(curr->bin.right, n->datatype);
      curr = NULL;
    } else if (curr->kind == AST_UNOP) {
      check_expr(curr->unop.operand, n->datatype);
      curr = NULL;
    }

    count++;
  }

  if (n->list.num && n->list.num != count)
    panic(&file, n->line, n->col, n->pos, SEM_LIST_SIZE_MISMATCH, NULL);
  if (count == 0)
    panic(&file, n->line, n->col, n->pos, SEM_LIST_EMPTY, NULL);
  if (n->list.num && n->list.num == 0)
    panic(&file, n->line, n->col, n->pos, SEM_LIST_NUM_IS_0, NULL);

  if (!n->list.num)
    n->list.num = count;

  if(!TQsemantic_declare(n->list.target->literal.raw, 
    n->list.target->datatype, n->list.target->ptr_to, n->list.is_mutable, true))
    panic(&file, n->line, n->col, n->pos, SEM_VAR_REDECL, n->list.target->literal.raw);

  return UNKNOWN;
}

extern "C" DataTypes_t semantic_index_handle(ASTNode_t *n) {
  // 1. Check the TARGET (the array itself)
  DataTypes_t target_t = check_expr(n->index.target, n->datatype);
  
  if (islist(n->index.target) && target_t != PTR) {
      panic(&file, n->line, n->col, n->pos, SEM_INDEX_NOT_ARRAY, NULL);
      return UNKNOWN;
  }

  // 2. Check the INDEX (must be an integer)
  DataTypes_t idx_t = check_expr(n->index.index, I32);
  if (idx_t != I32) {
      panic(&file, n->line, n->col, n->pos, SEM_INDEX_NOT_INT, NULL);
  }

  // 3. Return the element type (e.g., if list is i32[], return i32)
  return n->index.target->ptr_to; 
}

bool islist(ASTNode_t *target) {
  if (target->kind == AST_VAR) {
    SemanticSymbolRecord *symbol = TQ::semantic_symbol_table::semantic_find_symbol(target->var);
    return (symbol->type == PTR && TQsemantic_lookup_ptr_to(target->var) != UNKNOWN) && symbol->is_list && symbol;
  }
  return false;
}