#ifndef SEMANTIC_H
#define SEMANTIC_H

#include "../ast/ASTNode.h"

void semantic_check(ASTNode_t *root);
DataTypes_t check_expr(ASTNode_t *n);
void type_error(ASTNode_t *n, const char *msg);
int is_numeric(DataTypes_t t);
DataTypes_t promote(DataTypes_t a, DataTypes_t b);


#endif