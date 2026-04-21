#pragma once

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-include-dirs"
#pragma clang diagnostic ignored "-Wunknown-warning-option"

#ifdef __cplusplus
extern "C" {
#endif 
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
#include "stdlibs/stdlibs.h"
#include "builtin/builtin.h"

// Evaluation
#include "eval/eval.h"

#pragma clang diagnostic pop

#ifdef __cplusplus
} // extern "C"
#endif

// Utility headers (C++ only)
#include "utils/utf-8_lib/utf8.h"

// Code generation (C++)
#include "codegen/codegen.h"

