#!/bin/bash

PARSER_DIR="src/parser"
LEXER_DIR="src/lexer"
AST_DIR="src/ast"
EVAL_DIR="src/eval"
SEMAN="src/semantic"
UTILS="src/utils"
BIN_DIR="bin"

echo "Running bison to generate the parser..."
bison -d -o "$PARSER_DIR/parser.c" "$PARSER_DIR/parser.y" || exit 1

echo "Running flex to generate the lexer..."
flex -o "$LEXER_DIR/lexer.c" "$LEXER_DIR/lexer.l" || exit 1

echo "[3/3] Compiling..."
mkdir -p "$BIN_DIR"
gcc -Wall -Wextra -g -Isrc \
    $PARSER_DIR/parser.c \
    $LEXER_DIR/lexer.c \
    $EVAL_DIR/eval.c \
    $AST_DIR/ASTNode.c \
    $AST_DIR/ASTHelper.c \
    $AST_DIR/assigner.c \
    $AST_DIR/env.c \
    src/codegen/scm_codegen.c \
    $SEMAN/semanic.c \
    $SEMAN/symbol_table.c \
    $UTILS/printers/token_printer.c \
    $UTILS/printers/value_printer.c \
    $EVAL_DIR/stepper.c \
    $EVAL_DIR/eval_helper.c \
    $SEMAN/semantic_helper.c \
    src/main.c \
    -o "$BIN_DIR/Complier" -lm || exit 1

echo "Compiled successfully: $BIN_DIR/MyComplier"
