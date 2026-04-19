#!/bin/bash

set -euo pipefail

PARSER_DIR=$(find src/**/* -iname "parser.y" -exec dirname {} +;)
LEXER_DIR=$(find src/**/* -iname "lexer.l" -exec dirname {} +;)
BIN_DIR="bin"

LLVM_CONFIG=${LLVM_CONFIG:-llvm-config}

LLVM_CONFIG=${LLVM_CONFIG:-llvm-config}

LLVM_CXXFLAGS_RAW="$($LLVM_CONFIG --cxxflags)"

# Convert LLVM includes to -isystem to suppress warnings from external headers
LLVM_CXXFLAGS="$(echo "$LLVM_CXXFLAGS_RAW" | sed 's/-I\([^ ]*\)/-isystem \1/g')"
LLVM_LDFLAGS="$($LLVM_CONFIG --ldflags --libs core native)"

echo "Running bison to generate the parser..."
bison -d -o "$PARSER_DIR/parser.c" "$PARSER_DIR/parser.y"

echo "Running flex to generate the lexer..."
flex -o "$LEXER_DIR/lexer.c" "$LEXER_DIR/lexer.l"

mkdir -p "$BIN_DIR"

# C++ (LLVM/backend)
echo "Compiling [1/3] C++ Files"
CPP_SRC=($(find src -type f -iname "*.cpp"))
for src in "${CPP_SRC[@]}"; do
    obj="$BIN_DIR/$(basename "${src%.*}").o"
    clang++ -Wall -Wextra -g -Isrc $LLVM_CXXFLAGS -c "$src" -o "$obj"
done

# C sources
echo "Compiling [2/3] C Files"

C_SRC=($(find src -type f -iname "*.c"))
for src in "${C_SRC[@]}"; do
    obj="$BIN_DIR/$(basename "${src%.*}").o"
    gcc -Wall -Wextra -Wno-error -g -Isrc -Isrc/utils/utf-8_lib -c "$src" -o "$obj"
done

echo "Linking [3/3] Files..."
g++ -o "$BIN_DIR/TQC" "$BIN_DIR"/*.o -lm $LLVM_LDFLAGS

echo "Cleaning up object files..."
rm -f "$BIN_DIR"/*.o
