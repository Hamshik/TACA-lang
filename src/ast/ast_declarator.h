#ifndef AST_DECLARATOR_H
#define AST_DECLARATOR_H
#ifdef __cplusplus
extern "C" {
#endif

    #include "taca.h"
    #include "nodes.h"

    /* Constructors */
    ASTNode_t *new_num(char *rawval, DataTypes_t datatype, int line, int col);
    ASTNode_t *new_str(char *rawval, int line, int col);
    ASTNode_t *new_char_bytes(const char *bytes, size_t len, int line, int col);
    ASTNode_t *new_var(const char *name, DataTypes_t datatype, int line, int col);
    ASTNode_t *new_binop(ASTNode_t *l, ASTNode_t *r, int line, int col, OP_kind_t op);
    ASTNode_t *new_unop(ASTNode_t *e, int line, int col, OP_kind_t op);
    ASTNode_t *new_assign(ASTNode_t *lhs, ASTNode_t *rhs, DataTypes_t datatype, bool is_mutable, int line, int col, OP_kind_t op);
    ASTNode_t *new_if(ASTNode_t *cond, ASTNode_t *thenB, ASTNode_t *elseB, int line, int col);
    ASTNode_t *new_for(ASTNode_t *init, ASTNode_t *end, ASTNode_t *step, ASTNode_t *body, int line, int col);
    ASTNode_t *new_seq(ASTNode_t *a, ASTNode_t *b);
    ASTNode_t *new_while(ASTNode_t *cond, ASTNode_t *body, int line, int col);
    ASTNode_t* new_bool(bool val, int line, int col);
    ASTNode_t* new_fn_def(const char *name, Param_t *params, int param_count, DataTypes_t ret_type, ASTNode_t *body, int line, int col);
    ASTNode_t* new_fn_call(const char *name, ASTNode_t *args, int line, int col);
    ASTNode_t* new_return(ASTNode_t *value, int line, int col);
    ASTNode_t* new_import_node(const char *path, int line, int col);
    ASTNode_t* new_list(ASTNode_t *elements, ASTNode_t *target, DataTypes_t sub_type, size_t num ,bool is_mutable, int line, int col);
    ASTNode_t* new_index(ASTNode_t *var, ASTNode_t *index, int line, int col, bool islhs);
    /* Eval + memory */
    void ast_free(ASTNode_t *n);
    ASTNode_t *ast_alloc(void);

    /* Env */
    void set_var(const char *name, TQValue *val, DataTypes_t datatype);
    void set_var_current(const char *name, TQValue *val, DataTypes_t datatype);
    TQValue getvar(const char *name, DataTypes_t datatype, int line, int col, int pos);
    void env_push(void);
    void env_pop(void);
    void env_clear_all(void);
    void assign_value(DataTypes_t datatype, TQValue *dest, TQValue src);
    TQValue eval_assign(ASTNode_t *lhs, ASTNode_t *rhs, OP_kind_t op, DataTypes_t datatypes , int line, int col, int pos);
    TypedValue *getvar_ref(const char *name, int line, int col, int pos);
    int env_frame_id_of(const char *name, int line, int col, int pos);
    TypedValue *getvar_ref_at(int frame_id, const char *name, int line, int col, int pos);
    void set_var_at(int frame_id, const char *name, TQValue *val, DataTypes_t datatype, int line, int col, int pos);

#ifdef __cplusplus
}
#endif
#endif