#pragma once

#ifdef __cplusplus 
extern "C" {


#include "utils/colors.h"
#include "utils/error_handler/error.h"
#include "utils/uhash.h"

#include "ast/nodes.h"
#include "ast/ast_declarator.h"
#include "import/import.h"
#include "typechecker/typecheck.h"
#include "parser/parser.h"
#include "builtin/builtin.h"


}
// Semantic analysis (C++)
#include "semantic/semantic.hpp"

// Utility headers (C++ only)
#include "utils/utf-8_lib/utf8.h"

// Code generation (C++)
#include "codegen/codegen.h"

//libs cpp only
#include "stdlibs/stdlibs.h"

//symbol table
#include "SymbolTable/SymbolTable.hpp"

#endif
