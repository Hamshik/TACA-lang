#ifndef TARKIQ_H
#define TARKIQ_H

#ifdef __cplusplus
extern "C" {
#endif

#include "tarkiq/ast/ast_node.h"
#include "tarkiq/codegen/codegen.h"
#include "tarkiq/eval/eval.h"
#include "tarkiq/lexer/lexer_helpers.h"
#include "tarkiq/parser/parser_helpers.h"
#include "tarkiq/parser/parser.h"
#include "tarkiq/runtime/builtin.h"
#include "tarkiq/runtime/stdlibs.h"
#include "tarkiq/semantic/semantic.h"
#include "tarkiq/typechecker/typecheck.h"
#include "tarkiq/utf8/checked.h"
#include "tarkiq/utf8/core.h"
#include "tarkiq/utf8/unchecked.h"
#include "tarkiq/utf8/utf8.h"
#include "tarkiq/utils/colors.h"
#include "tarkiq/utils/error_msg.h"
#include "tarkiq/utils/uhash.h"

#ifdef __cplusplus
}
#endif

#endif // TARKIQ_H