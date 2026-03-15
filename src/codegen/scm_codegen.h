#ifndef SCM_CODEGEN_H
#define SCM_CODEGEN_H

#include "../ast/ASTNode.h"

// Returns a heap-allocated Scheme program string. Caller frees.
char *scm_codegen(ASTNode_t *root);

#endif

