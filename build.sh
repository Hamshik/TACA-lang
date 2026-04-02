#!/bin/bash

PARSER_DIR="src/parser"
LEXER_DIR="src/lexer"
AST_DIR="src/ast"
EVAL_DIR="src/eval"
SEMAN="src/semantic"
UTILS="src/utils"
BIN_DIR="bin"
BUILTIN="src/builtin"
DATASPEC="src/typechecker"

echo "Running bison to generate the parser..."
bison -d -o "$PARSER_DIR/parser.c" "$PARSER_DIR/parser.y" || exit 1

echo "Running flex to generate the lexer..."
flex -o "$LEXER_DIR/lexer.c" "$LEXER_DIR/lexer.l" || exit 1

echo "[3/3] Compiling..."
mkdir -p "$BIN_DIR"
gcc -Wall -Wextra -g -Isrc \
    $PARSER_DIR/parser.c \
    $PARSER_DIR/parser_helpers.c \
    $LEXER_DIR/lexer.c \
    $LEXER_DIR/lexer_helpers.c \
    $EVAL_DIR/eval.c \
    $AST_DIR/ASTNode.c \
    $AST_DIR/ASTHelper.c \
    $AST_DIR/assigner.c \
    $AST_DIR/env.c \
    $SEMAN/semanic.c \
    $SEMAN/symbol_table.c \
    $UTILS/error_handler/error.c \
    $UTILS/error_handler/error_msg.c \
    $EVAL_DIR/stepper.c \
    $EVAL_DIR/eval_helper.c \
    $SEMAN/semantic_helper.c \
    $BUILTIN/builtin.c \
    $DATASPEC/typecheck.c \
    src/main.c \
    -o "$BIN_DIR/Complier" -lm -Wunused-function -Wunused-variable -Wextra || exit 1

echo "Compiled successfully: $BIN_DIR/MyComplier"
