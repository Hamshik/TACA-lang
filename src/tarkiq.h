#ifndef TARKIQ_H
#define TARKIQ_H

#include "frontend/ast/ASTNode.h"
#include "utils/error_msg.h"
#include "utils/colors.h"
#include "utils/uhash.h"
#include "backend/codegen/codegen.h"
#include "middleend/semantic/semantic.h"
#include "middleend/eval/eval.h"
#include "middleend/typechecker/typecheck.h"
#include "frontend/lexer/lexer_helpers.h"
#include "frontend/parser/parser_helpers.h"
#include "runtime/builtin/builtin.h"
#include "runtime/stdlibs/stdlibs.h"
#include "utils/utf8/utf8.h"

#endif