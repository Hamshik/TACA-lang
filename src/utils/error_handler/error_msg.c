#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include "../colors.h"
#include <stdbool.h>
#include "error_msg.h"

const char *errc_msg(errc_t code) {
    switch (code) {
        case LEX_UNKNOWN_CHAR: return "unknown character";
        case LEX_INVALID_ESCAPE: return "invalid escape sequence";
        case PARSE_SYNTAX: return "syntax error";
        case PARSE_MISSING_SEMI: return "missing semicolon after statement";
        case PARSE_UNCLOSED_PAREN: return "missing closing parenthesis";
        case PARSE_UNCLOSED_BRACE: return "missing closing brace";
        case PARSE_UNCLOSED_BRACKET: return "missing closing bracket";

        case SEM_VAR_UNDECL: return "variable not declared";
        case SEM_VAR_TYPE_MISMATCH: return "variable type mismatch";
        case SEM_BINOP_INVALID: return "invalid operands for binary operator";
        case SEM_STRING_OP_INVALID: return "invalid string operation";
        case SEM_CMP_NEEDS_NUM: return "comparison needs numeric operands";
        case SEM_LOGIC_NEEDS_BOOL: return "logical operator needs bool operands";
        case SEM_NUMOP_NEEDS_NUM: return "numeric operator needs numeric operands";
        case SEM_NOT_NEEDS_BOOL: return "operator ! expects bool";
        case SEM_UNARY_NEEDS_NUM: return "unary operator expects numeric operand";
        case SEM_ASSIGN_TARGET_NOT_VAR: return "assignment target must be a variable";
        case SEM_VAR_REDECL: return "redeclaration of variable";
        case SEM_ASSIGN_TYPE_MISMATCH: return "type mismatch in assignment";
        case SEM_ASSIGN_IMMUTABLE: return "cannot assign to immutable variable";
        case SEM_IF_COND_NOT_BOOL: return "if condition must be boolean";
        case SEM_FOR_INIT_INVALID: return "for init must be an assignment/declaration";
        case SEM_FOR_INIT_NOT_NUM: return "for init variable must be numeric";
        case SEM_FOR_END_TYPE_MISMATCH: return "for end value must match init type";
        case SEM_FOR_STEP_TYPE_MISMATCH: return "for step value must match init type";
        case SEM_WHILE_COND_NOT_BOOL: return "while condition must be boolean";
        case SEM_FN_REDECL: return "redeclaration of function";
        case SEM_DUP_PARAM: return "duplicate parameter name";
        case SEM_CALL_UNDEF_FN: return "call to undefined function";
        case SEM_ARGC_MISMATCH: return "argument count mismatch";
        case SEM_ARG_TYPE_MISMATCH: return "argument type mismatch";
        case SEM_RETURN_OUTSIDE_FN: return "return outside of function";
        case SEM_RETURN_TYPE_MISMATCH: return "return type mismatch";
        case SEM_UNKNOWN_AST: return "unknown AST node in semantic analysis";

        case RT_NUM_LITERAL_UNSUPPORTED: return "unsupported numeric literal type";
        case RT_BINOP_UNSUPPORTED: return "unsupported type for binary operation";
        case RT_FOR_INIT_INVALID: return "invalid for loop init";
        case RT_FOR_STEP_ZERO: return "for loop step cannot be zero";
        case RT_CALL_UNDEF_FN: return "call to undefined function (runtime)";
        case RT_ARGC_MISMATCH: return "argument count mismatch (runtime)";
        case RT_UNKNOWN_AST: return "unknown AST node (runtime)";
        case RT_VAR_NOT_DEFINED: return "variable not defined (runtime)";
        case RT_VAR_TYPE_MISMATCH: return "type mismatch for variable (runtime)";
        case RT_ASSIGN_TARGET_NOT_VAR: return "assignment target must be a variable (runtime)";
        case RT_ASSIGN_UNSUPPORTED: return "unsupported assignment type (runtime)";

        default: return "error";
    }
}

char *logf_msg(const char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);

    int n = vsnprintf(NULL, 0, fmt, ap);
    va_end(ap);

    if (n < 0) return NULL;

    char *buf = malloc((size_t)n + 1);
    if (!buf) return NULL;

    va_start(ap, fmt);
    vsnprintf(buf, (size_t)n + 1, fmt, ap);
    va_end(ap);

    return buf;
}
