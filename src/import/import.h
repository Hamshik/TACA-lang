#pragma once

#include "taca.h"

ASTNode_t* parse_file(FILE *f);
void yyrestart(FILE *input_file);
