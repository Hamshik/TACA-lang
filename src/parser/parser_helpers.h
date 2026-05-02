#ifndef PARSER_HELPERS_H
#define PARSER_HELPERS_H

#include <stdbool.h>

#include "taca.h"

void  TQannotate_decl_list(ASTNode_t *n, DataTypes_t default_t, DataTypes_t default_sub_type, bool is_mutable);

#endif
