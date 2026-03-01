#ifndef EVAL_H
#define EVAL_H
#include "../ast/ASTNode.h"


Value ast_eval(ASTNode_t *node);
void do_operation_str(char **result, const char* a, const char* b, OP_kind_t op);
Value eval_bool(OP_kind_t op, bool a, bool b);
void do_unop_operation(Value *result, Value *operand,DataTypes_t datatype,OP_kind_t op);
Value eval_binop_double(OP_kind_t op, double a, double b);
Value eval_binop_float(OP_kind_t op, float a, float b);
Value eval_binop_int(OP_kind_t op, bool isShort, int a, int b);
OP_kind_t get_assign_op(OP_kind_t op);

#endif