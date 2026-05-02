#pragma once

#ifndef __cplusplus
// Utility headers (C parts)
#include "utils/colors.h"
#include "utils/uhash.h"
#include "utils/error_handler/error.h" 

// AST and semantic analysis
#include "ast/ast_enum.h"
#include "ast/nodes.h"
#include "ast/ast_declarator.h"
#include "semantic/semantic.hpp" 

// Frontend headers
#include "parser/parser.h"
#include "lexer/lexer.h"
#include "parser/parser_helpers.h"

// Type checking
#include "typechecker/typecheck.h"

// Standard libraries and builtins
#include "builtin/builtin.h"

// Evaluation
#include "eval/eval.h"

//codegen
#include "codegen/codegen.h"

//import system
#include "import/import.h"

#include "cmd-exec/cmd-exec.h"
#endif