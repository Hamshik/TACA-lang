#include "scm_codegen.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *buf;
    size_t len;
    size_t cap;
} StrBuf;

static void sb_grow(StrBuf *sb, size_t need) {
    if (sb->len + need + 1 <= sb->cap) return;
    size_t ncap = sb->cap ? sb->cap : 256;
    while (ncap < sb->len + need + 1) ncap *= 2;
    char *nb = realloc(sb->buf, ncap);
    if (!nb) { perror("realloc"); exit(1); }
    sb->buf = nb;
    sb->cap = ncap;
}

static void sb_putc(StrBuf *sb, char c) {
    sb_grow(sb, 1);
    sb->buf[sb->len++] = c;
    sb->buf[sb->len] = '\0';
}

static void sb_puts(StrBuf *sb, const char *s) {
    size_t n = strlen(s);
    sb_grow(sb, n);
    memcpy(sb->buf + sb->len, s, n);
    sb->len += n;
    sb->buf[sb->len] = '\0';
}

static void emit_expr(StrBuf *sb, ASTNode_t *n);
static void emit_stmt(StrBuf *sb, ASTNode_t *n, int in_fn);

static void emit_string(StrBuf *sb, const char *raw) {
    sb_putc(sb, '"');
    for (const char *p = raw; p && *p; p++) {
        if (*p == '"' || *p == '\\') sb_putc(sb, '\\');
        sb_putc(sb, *p);
    }
    sb_putc(sb, '"');
}

static const char *binop_name(OP_kind_t op) {
    switch (op) {
        case OP_ADD: return "+";
        case OP_SUB: return "-";
        case OP_MUL: return "*";
        case OP_DIV: return "quotient";
        case OP_MOD: return "modulo";
        case OP_POW: return "expt";
        case OP_AND: return "and";
        case OP_OR: return "or";
        case OP_EQ: return "=";
        case OP_NEQ: return "not=";
        case OP_LT: return "<";
        case OP_LE: return "<=";
        case OP_GT: return ">";
        case OP_GE: return ">=";
        case OP_LSHIFT: return "ash";
        case OP_RSHIFT: return "ash";
        case OP_BITAND: return "logand";
        case OP_BITOR: return "logior";
        case OP_BITXOR: return "logxor";
        default: return NULL;
    }
}

static int is_value_expr(ASTNode_t *n) {
    if (!n) return 0;
    switch (n->kind) {
        case AST_NUM:
        case AST_STR:
        case AST_BOOL:
        case AST_VAR:
        case AST_BINOP:
        case AST_UNOP:
        case AST_CALL:
            return 1;
        default:
            return 0;
    }
}

static void emit_arg_list(StrBuf *sb, ASTNode_t *args) {
    // args is an AST_SEQ list where seq.a is the current arg, seq.b is the rest
    for (ASTNode_t *it = args; it; ) {
        ASTNode_t *cur = (it->kind == AST_SEQ) ? it->seq.a : it;
        sb_putc(sb, ' ');
        emit_expr(sb, cur);
        if (it->kind == AST_SEQ) it = it->seq.b;
        else it = NULL;
    }
}

static void emit_expr(StrBuf *sb, ASTNode_t *n) {
    if (!n) { sb_puts(sb, "0"); return; }

    switch (n->kind) {
        case AST_NUM:
            sb_puts(sb, n->literal.raw ? n->literal.raw : "0");
            return;
        case AST_STR:
            emit_string(sb, n->literal.raw ? n->literal.raw : "");
            return;
        case AST_BOOL:
            sb_puts(sb, (n->literal.raw && n->literal.raw[0] == 't') ? "#t" : "#f");
            return;
        case AST_VAR:
            sb_puts(sb, n->var);
            return;
        case AST_BINOP: {
            // Special-case string concat: Tarkiq uses + for strings.
            if (n->datatype == STRINGS && n->bin.op == OP_ADD) {
                sb_puts(sb, "(string-append ");
                emit_expr(sb, n->bin.left);
                sb_putc(sb, ' ');
                emit_expr(sb, n->bin.right);
                sb_putc(sb, ')');
                return;
            }

            const char *op = binop_name(n->bin.op);
            if (!op) { sb_puts(sb, "0"); return; }
            sb_putc(sb, '(');
            sb_puts(sb, op);
            sb_putc(sb, ' ');
            emit_expr(sb, n->bin.left);
            sb_putc(sb, ' ');
            if (n->bin.op == OP_RSHIFT) {
                // ash right shift: (ash x (- k))
                sb_puts(sb, "(- ");
                emit_expr(sb, n->bin.right);
                sb_putc(sb, ')');
            } else {
                emit_expr(sb, n->bin.right);
            }
            sb_putc(sb, ')');
            return;
        }
        case AST_UNOP: {
            switch (n->unop.op) {
                case OP_NOT:
                    sb_puts(sb, "(not ");
                    emit_expr(sb, n->unop.operand);
                    sb_putc(sb, ')');
                    return;
                case OP_BITNOT:
                    sb_puts(sb, "(lognot ");
                    emit_expr(sb, n->unop.operand);
                    sb_putc(sb, ')');
                    return;
                case OP_NEG:
                    sb_puts(sb, "(- ");
                    emit_expr(sb, n->unop.operand);
                    sb_putc(sb, ')');
                    return;
                case OP_POS:
                    emit_expr(sb, n->unop.operand);
                    return;
                case OP_INC:
                    // (begin (set! x (+ x 1)) x)
                    sb_puts(sb, "(begin (set! ");
                    emit_expr(sb, n->unop.operand);
                    sb_puts(sb, " (+ ");
                    emit_expr(sb, n->unop.operand);
                    sb_puts(sb, " 1)) ");
                    emit_expr(sb, n->unop.operand);
                    sb_putc(sb, ')');
                    return;
                case OP_DEC:
                    sb_puts(sb, "(begin (set! ");
                    emit_expr(sb, n->unop.operand);
                    sb_puts(sb, " (- ");
                    emit_expr(sb, n->unop.operand);
                    sb_puts(sb, " 1)) ");
                    emit_expr(sb, n->unop.operand);
                    sb_putc(sb, ')');
                    return;
                default:
                    sb_puts(sb, "0");
                    return;
            }
        }
        case AST_CALL:
            sb_putc(sb, '(');
            sb_puts(sb, n->call.name);
            emit_arg_list(sb, n->call.args);
            sb_putc(sb, ')');
            return;
        case AST_ASSIGN:
            // Used in expressions in Tarkiq; in Scheme treat as statement-y begin.
            sb_puts(sb, "(begin ");
            emit_stmt(sb, n, 0);
            sb_puts(sb, " 0)");
            return;
        default:
            sb_puts(sb, "0");
            return;
    }
}

static void emit_block(StrBuf *sb, ASTNode_t *n, int in_fn) {
    if (!n) { sb_puts(sb, "(begin)"); return; }
    if (n->kind == AST_SEQ) {
        sb_puts(sb, "(begin ");
        emit_stmt(sb, n->seq.a, in_fn);
        sb_putc(sb, ' ');
        emit_stmt(sb, n->seq.b, in_fn);
        sb_putc(sb, ')');
        return;
    }
    // single statement
    sb_puts(sb, "(begin ");
    emit_stmt(sb, n, in_fn);
    sb_putc(sb, ')');
}

static void emit_stmt(StrBuf *sb, ASTNode_t *n, int in_fn) {
    if (!n) return;

    switch (n->kind) {
        case AST_SEQ:
            emit_stmt(sb, n->seq.a, in_fn);
            sb_putc(sb, '\n');
            emit_stmt(sb, n->seq.b, in_fn);
            return;

        case AST_FN: {
            sb_puts(sb, "(define (");
            sb_puts(sb, n->fn_def.name);
            for (int i = 0; i < n->fn_def.param_count; i++) {
                sb_putc(sb, ' ');
                sb_puts(sb, n->fn_def.params[i].name);
            }
            sb_puts(sb, ")\n  (call/cc (lambda (return)\n    ");
            emit_block(sb, n->fn_def.body, 1);
            sb_puts(sb, "\n  )))\n");
            return;
        }

        case AST_RETURN:
            sb_puts(sb, "(return ");
            if (n->ret_stmt.value) emit_expr(sb, n->ret_stmt.value);
            else sb_puts(sb, "0");
            sb_putc(sb, ')');
            return;

        case NODE_IF:
            sb_puts(sb, "(if ");
            emit_expr(sb, n->ifnode.cond);
            sb_putc(sb, ' ');
            emit_block(sb, n->ifnode.then_branch, in_fn);
            sb_putc(sb, ' ');
            if (n->ifnode.else_branch) emit_block(sb, n->ifnode.else_branch, in_fn);
            else sb_puts(sb, "(begin)");
            sb_putc(sb, ')');
            return;

        case NODE_FOR: {
            // Compile to: init; (let ((end ...) (step ...)) (let loop () (if cond (begin body (set! i (+ i step)) (loop)) 'done)))
            const char *ivar = n->fornode.init->assign.lhs->var;

            sb_puts(sb, "(begin ");
            emit_stmt(sb, n->fornode.init, in_fn);
            sb_putc(sb, '\n');
            sb_puts(sb, "(let ((end ");
            emit_expr(sb, n->fornode.end);
            sb_puts(sb, ") (step ");
            if (n->fornode.step) emit_expr(sb, n->fornode.step);
            else sb_puts(sb, "1");
            sb_puts(sb, "))\n  (let loop ()\n    (if (if (> step 0) (< ");
            sb_puts(sb, ivar);
            sb_puts(sb, " end) (> ");
            sb_puts(sb, ivar);
            sb_puts(sb, " end))\n        (begin ");
            emit_block(sb, n->fornode.body, in_fn);
            sb_puts(sb, "\n          (set! ");
            sb_puts(sb, ivar);
            sb_puts(sb, " (+ ");
            sb_puts(sb, ivar);
            sb_puts(sb, " step))\n          (loop))\n        'done)))");
            sb_puts(sb, ")");
            return;
        }

        case AST_WHILE:
            sb_puts(sb, "(let loop () (if ");
            emit_expr(sb, n->whilenode.cond);
            sb_puts(sb, " (begin ");
            emit_block(sb, n->whilenode.body, in_fn);
            sb_puts(sb, " (loop)) 'done))");
            return;

        case AST_ASSIGN: {
            if (n->assign.op == OP_ASSIGN && n->assign.is_declaration) {
                sb_puts(sb, "(define ");
                sb_puts(sb, n->assign.lhs->var);
                sb_putc(sb, ' ');
                emit_expr(sb, n->assign.rhs);
                sb_putc(sb, ')');
                return;
            }

            // x = e; or x += e; ...
            sb_puts(sb, "(set! ");
            sb_puts(sb, n->assign.lhs->var);
            sb_putc(sb, ' ');
            switch (n->assign.op) {
                case OP_ASSIGN:
                    emit_expr(sb, n->assign.rhs);
                    break;
                case OP_PLUS_ASSIGN:
                    sb_puts(sb, "(+ ");
                    sb_puts(sb, n->assign.lhs->var);
                    sb_putc(sb, ' ');
                    emit_expr(sb, n->assign.rhs);
                    sb_putc(sb, ')');
                    break;
                case OP_MINUS_ASSIGN:
                    sb_puts(sb, "(- ");
                    sb_puts(sb, n->assign.lhs->var);
                    sb_putc(sb, ' ');
                    emit_expr(sb, n->assign.rhs);
                    sb_putc(sb, ')');
                    break;
                case OP_MUL_ASSIGN:
                    sb_puts(sb, "(* ");
                    sb_puts(sb, n->assign.lhs->var);
                    sb_putc(sb, ' ');
                    emit_expr(sb, n->assign.rhs);
                    sb_putc(sb, ')');
                    break;
                case OP_DIV_ASSIGN:
                    sb_puts(sb, "(quotient ");
                    sb_puts(sb, n->assign.lhs->var);
                    sb_putc(sb, ' ');
                    emit_expr(sb, n->assign.rhs);
                    sb_putc(sb, ')');
                    break;
                case OP_MOD_ASSIGN:
                    sb_puts(sb, "(modulo ");
                    sb_puts(sb, n->assign.lhs->var);
                    sb_putc(sb, ' ');
                    emit_expr(sb, n->assign.rhs);
                    sb_putc(sb, ')');
                    break;
                case OP_POW_ASSIGN:
                    sb_puts(sb, "(expt ");
                    sb_puts(sb, n->assign.lhs->var);
                    sb_putc(sb, ' ');
                    emit_expr(sb, n->assign.rhs);
                    sb_putc(sb, ')');
                    break;
                case OP_LSHIFT_ASSIGN:
                    sb_puts(sb, "(ash ");
                    sb_puts(sb, n->assign.lhs->var);
                    sb_putc(sb, ' ');
                    emit_expr(sb, n->assign.rhs);
                    sb_putc(sb, ')');
                    break;
                case OP_RSHIFT_ASSIGN:
                    sb_puts(sb, "(ash ");
                    sb_puts(sb, n->assign.lhs->var);
                    sb_puts(sb, " (- ");
                    emit_expr(sb, n->assign.rhs);
                    sb_putc(sb, ')');
                    sb_putc(sb, ')');
                    break;
                default:
                    emit_expr(sb, n->assign.rhs);
                    break;
            }
            sb_putc(sb, ')');
            return;
        }

        default:
            // Expression statement
            if (!in_fn && is_value_expr(n)) {
                sb_puts(sb, "(begin (display ");
                emit_expr(sb, n);
                sb_puts(sb, ") (newline))");
            } else {
                emit_expr(sb, n);
            }
            return;
    }
}

char *scm_codegen(ASTNode_t *root) {
    StrBuf sb = {0};
    sb_puts(&sb, ";; Generated from Tarkiq AST\n");
    sb_puts(&sb, "(begin\n");
    emit_stmt(&sb, root, 0);
    sb_puts(&sb, "\n)\n");
    return sb.buf ? sb.buf : strdup("");
}
