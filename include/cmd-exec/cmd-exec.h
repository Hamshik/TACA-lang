#pragma once

#include <errno.h>
#include <limits.h>
#include <linux/limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

struct file_t;
struct ASTNode_t;


/* Program options structure */
typedef struct {
    const char *input_filename;
    char* bin_output_path;
    bool emit_ir;
    char* ir_output_path;
} Options;

int run_exec(const char *prog, char *const argv[]);
FILE *open_file(const char *filename, char **resolved_path_out);
bool parse_arguments(int argc, char **argv, Options *opts);
bool setup_input_file(const Options *opts, file_t *file);
int compile_and_execute(ASTNode_t *root, const Options *opts);
void yyrestart(FILE *input_file);