#ifndef PARSER_HELPERS_H
#define PARSER_HELPERS_H

#include <stdbool.h>

#include "../taca.h"

void tq_annotate_decl_list(ASTNode_t *n, DataTypes_t default_t, DataTypes_t default_ptr_to, bool is_mutable);

#endif
