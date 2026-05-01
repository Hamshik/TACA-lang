#!/bin/bash

set -euo pipefail

PARSER_DIR=$(find src/**/* -iname "*.y" -exec dirname {} +;)
LEXER_DIR=$(find src/**/* -iname "*.l" -exec dirname {} +;)
BIN_DIR="bin"

LLVM_CONFIG=${LLVM_CONFIG:-llvm-config-22}

if command -v "$LLVM_CONFIG" >/dev/null 2>&1; then
    LLVM_CXXFLAGS="$($LLVM_CONFIG --cxxflags)"
    LLVM_LDFLAGS="$($LLVM_CONFIG --ldflags --system-libs --libs core native)"
else
    echo "Error: llvm-config not found. Please install LLVM and ensure llvm-config is in your PATH."
    exit 1
fi

echo "Running bison to generate the parser..."
bison -d --graph -o "$PARSER_DIR/parser.c" "$PARSER_DIR/parser.y"

echo "Running flex to generate the lexer..."
flex -o "$LEXER_DIR/lexer.c" "$LEXER_DIR/lexer.l"

mkdir -p "$BIN_DIR"

# C++ (LLVM/backend)
echo "Compiling [1/3] C++ Files"

for src in $(find src -type f -iname "*.cpp"); do
    obj="$BIN_DIR/$(basename "${src%.*}").o"
    clang++ -fcxx-exceptions -w -Wall -Wextra -g -O0 $LLVM_CXXFLAGS -Isrc -c "$src" -o "$obj"
done

# C sources
echo "Compiling [2/3] C Files"

for src in $(find src -type f -iname "*.c"); do
    obj="$BIN_DIR/$(basename "${src%.*}").o"
    clang -Wall -Wextra -g -O0 -Isrc -c "$src" -o "$obj"
done

echo "Linking [3/3] Files..."
clang++ -o "$BIN_DIR/taca" "$BIN_DIR"/*.o -lm $LLVM_LDFLAGS

echo "Cleaning up object files..."
rm -f "$BIN_DIR"/*.o
