#pragma once

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-include-dirs"
#pragma clang diagnostic ignored "-Wunknown-warning-option"

// Utility headers (C parts)
#include "utils/uhash.h"
#include "utils/colors.h"
#include "utils/error_handler/error.h"

// AST and semantic analysis
#include "ast/ASTNode.h"
#include "semantic/semantic.h"

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

#pragma clang diagnostic pop