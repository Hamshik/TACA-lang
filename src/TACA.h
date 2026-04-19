#pragma once

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-include-dirs"
#pragma clang diagnostic ignored "-Wunknown-warning-option"

// Utility headers
#include "utils/utils.h"
#include "utils/colors.h"
#include "utils/error/error.h"
#include "utils/uhash.h"

// Frontend headers
#include "lexer/lexer.h"
#include "parser/parser.h"
#include "parser/parser_helpers.h"

// AST and semantic analysis
#include "ast/ASTNode.h"
#include "semantic/semantic.h"

// Type checking
#include "typechecker/typecheck.h"

// Code generation
#include "codegen/codegen.h"

// Standard libraries and builtins
#include "stdlibs/stdlibs.h"
#include "builtin/builtin.h"

// Evaluation
#include "eval/eval.h"

#pragma clang diagnostic pop
