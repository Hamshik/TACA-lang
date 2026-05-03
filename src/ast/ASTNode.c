#include "ast/nodes.h"
#include "ast/ast_declarator.h"
#include "ast/ast_enum.h"
#include <string.h>
#include <stdlib.h>
#include "parser/location.h"
#include <stdbool.h>

ASTNode_t* new_num(char *rawval, DataTypes_t datatype, TQLocation TQloc) {

    ASTNode_t *node = ast_alloc();
    node->kind = AST_NUM;
    node->datatype = datatype;
    node->loc = TQloc;
    node->literal.raw = strdup(rawval);   // copy value
    return node;
}

ASTNode_t *new_str(char *rawval, TQLocation TQloc)
{
    ASTNode_t *node = ast_alloc();
    node->kind = AST_STR;
    node->datatype = STRINGS;
    node->loc = TQloc;    
    node->literal.raw = strdup(rawval);   // copy value
    return node;
}

ASTNode_t *new_char_bytes(const char *bytes, size_t len, TQLocation TQloc)
{
    ASTNode_t *node = ast_alloc();
    node->kind = AST_CHAR;
    node->datatype = CHARACTER;
    node->loc = TQloc;
    node->literal.len = len;
    node->literal.raw = malloc(len + 1);
    if (node->literal.raw && bytes) {
        memcpy(node->literal.raw, bytes, len);
        node->literal.raw[len] = '\0'; /* keep NUL-terminated copy */
    }
    return node;
}

ASTNode_t* new_var(const char *name, DataTypes_t datatype, TQLocation TQloc) {
    ASTNode_t *node = ast_alloc();
    node->kind = AST_VAR;
    node->var = strdup(name);
    node->datatype = datatype;
    node->loc = TQloc;
    return node;
}

ASTNode_t* new_unop(ASTNode_t *operand, TQLocation TQloc, OP_kind_t op) {
    ASTNode_t *node = ast_alloc();
    node->kind = AST_UNOP;
    node->unop.op = op;
    node->datatype = operand->datatype;
    node->unop.operand = operand;
    node->loc = TQloc;
    return node;
}

ASTNode_t* new_binop(ASTNode_t *left, ASTNode_t *right, TQLocation TQloc, OP_kind_t op) {
    ASTNode_t *node = ast_alloc();
    node->kind = AST_BINOP;
    node->datatype = UNKNOWN;
    node->bin.op = op;
    node->bin.left = left;
    node->bin.right = right;
    node->loc = TQloc;
    return node;
}

ASTNode_t* new_assign(
    ASTNode_t *lhs, ASTNode_t *rhs, DataTypes_t datatype, bool is_mutable, TQLocation TQloc, OP_kind_t op
) {
    ASTNode_t *node = ast_alloc();
    node->kind = AST_ASSIGN;
    node->assign.op = op;
    node->assign.lhs = lhs;
    node->assign.rhs = rhs;
    node->datatype = datatype;
    node->assign.is_mutable = is_mutable;
    node->assign.is_declaration = false;
    node->loc = TQloc;
    node->assign.is_autotyped = (datatype == UNKNOWN);
    return node;
}

ASTNode_t* new_seq(ASTNode_t *a, ASTNode_t *b) {
    ASTNode_t *node = ast_alloc();
    node->kind = AST_SEQ;
    node->seq.a = a;
    node->seq.b = b;
    return node;
}

ASTNode_t *new_while(ASTNode_t *cond, ASTNode_t *body, TQLocation TQloc) {
    ASTNode_t *node = ast_alloc();
    node->kind = AST_WHILE;
    node->whilenode.cond = cond;
    node->whilenode.body = body;
    node->loc = TQloc;
    return node;
}

ASTNode_t* new_if(ASTNode_t *cond, ASTNode_t *thenB, ASTNode_t *elseB, TQLocation TQloc) {
    ASTNode_t *node = ast_alloc();
    node->kind = NODE_IF;
    node->ifnode.cond = cond;
    node->ifnode.then_branch = thenB;
    node->ifnode.else_branch = elseB;
    node->loc = TQloc;;
    return node;
}

ASTNode_t* new_for(ASTNode_t *init, ASTNode_t *end, ASTNode_t *step, ASTNode_t *body, TQLocation TQloc) {
    ASTNode_t *node = ast_alloc();
    node->kind = NODE_FOR;
    node->fornode.init = init;
    node->fornode.end = end;
    node->fornode.step = step;
    node->fornode.body = body;
    node->loc = TQloc;;
    return node;
}

ASTNode_t* new_bool(bool val, TQLocation TQloc) {
    ASTNode_t *node = ast_alloc();
    node->kind = AST_BOOL;
    node->datatype = BOOL;
    node->loc = TQloc;
    node->literal.raw = strdup(val ? "true" : "false");
    return node;
}

ASTNode_t *new_fn_def(
    const char *name, Param_t *params, int param_count, DataTypes_t ret_type, ASTNode_t *body, TQLocation TQloc
){
    ASTNode_t *node = ast_alloc();
    node->kind = AST_FN;
    node->fn_def.name = strdup(name);
    node->fn_def.params = params;
    node->fn_def.param_count = param_count;
    node->fn_def.ret = ret_type;
    node->fn_def.body = body;
    node->loc = TQloc;
    return node;
}

ASTNode_t *new_fn_call(const char *name, ASTNode_t *args, TQLocation TQloc) {
    ASTNode_t *node = ast_alloc();
    node->kind = AST_CALL;
    node->call.name = strdup(name);
    node->call.args = args;
    node->loc = TQloc;
    return node;
}

ASTNode_t *new_return(ASTNode_t *value, TQLocation TQloc) {
    ASTNode_t *node = ast_alloc();
    node->kind = AST_RETURN;
    node->ret_stmt.value = value;
    node->loc = TQloc;
    return node;
}

ASTNode_t* new_import_node(const char* path, TQLocation TQloc) {
    ASTNode_t* node = ast_alloc();
    node->kind = AST_IMPORT;
    node->importNode.path = strdup(path);
    node->loc = TQloc;
    return node;
}

ASTNode_t* new_list(ASTNode_t *elements, ASTNode_t *target, DataTypes_t sub_type, size_t num ,bool is_mutable, TQLocation TQloc) {
    ASTNode_t *node = ast_alloc();
    node->kind = AST_LIST;
    node->list.elements = elements;
    node->list.target = target;
    node->datatype = LIST;
    node->sub_type = sub_type;
    node->list.is_mutable = is_mutable;
    node->loc = TQloc;
    node->list.num = num;
    return node;
}

ASTNode_t* new_index(ASTNode_t *var, ASTNode_t *index, bool islhs, TQLocation TQloc) {
    ASTNode_t *node = ast_alloc();
    node->kind = AST_INDEX;
    node->index.target = var;
    node->index.index = index;
    node->index.islhs = islhs;
    node->loc = TQloc;
    return node;
}