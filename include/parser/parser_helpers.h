#pragma once

#include <stdbool.h>
#include "utils/error_handler/error.h"
#include "location.h"
#include "ast/ast_enum.h"

struct ASTNode_t;

extern int g_last_parse_err_line;
extern int g_last_parse_err_col;
extern int g_last_parse_err_pos;
extern const char *g_last_parse_err_msg;

void TQannotate_decl_list(ASTNode_t *n, DataTypes_t default_t, DataTypes_t default_sub_type, bool is_mutable);
