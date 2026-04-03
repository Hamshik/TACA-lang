#!/bin/bash

set -euo pipefail

PARSER_DIR="src/parser"
LEXER_DIR="src/lexer"
AST_DIR="src/ast"
EVAL_DIR="src/eval"
SEMAN="src/semantic"
UTILS="src/utils"
BIN_DIR="bin"
BUILTIN="src/builtin"
DATASPEC="src/typechecker"
CODEGEN="src/codegen"
STDLIBS="src/stdlibs"

LLVM_CONFIG=${LLVM_CONFIG:-llvm-config}
if command -v "$LLVM_CONFIG" >/dev/null 2>&1; then
    LLVM_CXXFLAGS="$($LLVM_CONFIG --cxxflags)"
    LLVM_LDFLAGS="$($LLVM_CONFIG --ldflags --libs core native)"
else
    LLVM_CXXFLAGS=""
    LLVM_LDFLAGS=""
fi

echo "Running bison to generate the parser..."
bison -d -o "$PARSER_DIR/parser.c" "$PARSER_DIR/parser.y"

echo "Running flex to generate the lexer..."
flex -o "$LEXER_DIR/lexer.c" "$LEXER_DIR/lexer.l"

mkdir -p "$BIN_DIR"

echo "Compling[1/3] C++ Files"

CPP_SRCS=(
    "$CODEGEN/codegen.cpp"
    "$CODEGEN/helper.cpp"
    "$STDLIBS/printer.cpp"
    "$CODEGEN/handle_loops.cpp"
    "$CODEGEN/emit_expr.cpp"
    "$CODEGEN/handle_fn.cpp"
    "$CODEGEN/op_handler.cpp"
)

# C++ (LLVM/backend)
for src in "${CPP_SRCS[@]}"; do
    obj="$BIN_DIR/$(basename "${src%.*}").o"
    g++ -Wall -Wextra -g -Isrc -w $LLVM_CXXFLAGS -c "$src" -o "$obj"
done

# C sources
echo "Compling[2/3] C Files"
C_SRCS=(
    "$PARSER_DIR/parser.c"
    "$PARSER_DIR/parser_helpers.c"
    "$LEXER_DIR/lexer.c"
    "$LEXER_DIR/lexer_helpers.c"
    "$EVAL_DIR/eval.c"
    "$AST_DIR/ASTNode.c"
    "$AST_DIR/ASTHelper.c"
    "$AST_DIR/assigner.c"
    "$AST_DIR/env.c"
    "$SEMAN/semanic.c"
    "$SEMAN/symbol_table.c"
    "$UTILS/error_handler/error.c"
    "$UTILS/error_handler/error_msg.c"
    "$EVAL_DIR/stepper.c"
    "$EVAL_DIR/eval_helper.c"
    "$SEMAN/semantic_helper.c"
    "$BUILTIN/builtin.c"
    "$DATASPEC/typecheck.c"
    "src/main.c"
)

for src in "${C_SRCS[@]}"; do
    obj="$BIN_DIR/$(basename "${src%.*}").o"
    gcc -Wall -Wextra -g -Isrc -Wunused-function -Wunused-variable -c "$src" -o "$obj"
done

echo "Linking[3/3] Files..."
g++ -o "$BIN_DIR/TQC" "$BIN_DIR"/*.o -lm $LLVM_LDFLAGS

echo "Cleaning up object files..."
rm -f "$BIN_DIR"/*.o

echo "Compiled successfully: $BIN_DIR/TQC"
