#ifndef AST_DECLARATOR_H
#define AST_DECLARATOR_H
#ifdef __cplusplus
extern "C" {
#endif
    #include "nodes.h"

    /* Constructors */
    ASTNode_t *new_num(char *rawval, DataTypes_t datatype, TQLocation loc);
    ASTNode_t *new_str(char *rawval, TQLocation loc);
    ASTNode_t *new_char_bytes(const char *bytes, size_t len, TQLocation loc);
    ASTNode_t *new_var(const char *name, DataTypes_t datatype, TQLocation loc);
    ASTNode_t *new_binop(ASTNode_t *l, ASTNode_t *r, TQLocation loc, OP_kind_t op);
    ASTNode_t *new_unop(ASTNode_t *e, TQLocation loc, OP_kind_t op);
    ASTNode_t *new_assign(ASTNode_t *lhs, ASTNode_t *rhs, DataTypes_t datatype, bool is_mutable, TQLocation loc, OP_kind_t op);
    ASTNode_t *new_if(ASTNode_t *cond, ASTNode_t *thenB, ASTNode_t *elseB, TQLocation loc);
    ASTNode_t *new_for(ASTNode_t *init, ASTNode_t *end, ASTNode_t *step, ASTNode_t *body, TQLocation loc);
    ASTNode_t *new_seq(ASTNode_t *a, ASTNode_t *b);
    ASTNode_t *new_while(ASTNode_t *cond, ASTNode_t *body, TQLocation loc);
    ASTNode_t* new_bool(bool val, TQLocation loc);
    ASTNode_t* new_fn_def(const char *name, Param_t *params, int param_count, DataTypes_t ret_type, ASTNode_t *body, TQLocation loc);
    ASTNode_t* new_fn_call(const char *name, ASTNode_t *args, TQLocation loc);
    ASTNode_t* new_return(ASTNode_t *value, TQLocation loc);
    ASTNode_t* new_import_node(const char *path, TQLocation loc);
    ASTNode_t* new_list(ASTNode_t *elements, ASTNode_t *target, DataTypes_t sub_type, size_t num ,bool is_mutable, TQLocation loc);
    ASTNode_t* new_index(ASTNode_t *var, ASTNode_t *index, bool islhs, TQLocation loc);
    /* Eval + memory */
    void ast_free(ASTNode_t *n);
    ASTNode_t *ast_alloc(void);

#ifdef __cplusplus
}
#endif
#endif