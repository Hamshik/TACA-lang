#include "../colors.h"
#include "error_msg.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char *read_entire_path(const char *path, size_t *out_len) {
    if (!path) return NULL;
    FILE *f = fopen(path, "rb");
    if (!f) return NULL;

    if (fseek(f, 0, SEEK_END) != 0) { fclose(f); return NULL; }
    long n = ftell(f);
    if (n < 0) { fclose(f); return NULL; }
    rewind(f);

    char *buf = malloc((size_t)n + 1);
    if (!buf) { fclose(f); return NULL; }

    size_t got = fread(buf, 1, (size_t)n, f);
    fclose(f);
    buf[got] = '\0';
    if (out_len) *out_len = got;
    return buf;
}

static int digits_int(int v) {
    int d = 1;
    while (v >= 10) { v /= 10; d++; }
    return d;
}

void panic(
    file_t *file,
    int err_line,
    int err_col,
    int ini_pos,
    const char *message
){
    const char *filename = (file && file->filename) ? file->filename : "<input>";
    const char *msg = message ? message : "error";

    size_t src_len = 0;
    char *src = read_entire_path(filename, &src_len);

    fprintf(stderr, BOLD RED "error: %s\n" RESET, msg);
    fprintf(stderr, BOLD DIM " --> %s:%d:%d\n" RESET, filename, err_line, err_col);

    if (!src || src_len == 0) {
        free(src);
        exit(EXIT_FAILURE);
    }

    size_t pos = (ini_pos < 0) ? 0u : (size_t)ini_pos;
    if (pos >= src_len) pos = src_len - 1;

    size_t line_start = pos;
    while (line_start > 0 && src[line_start - 1] != '\n') line_start--;

    size_t line_end = pos;
    while (line_end < src_len && src[line_end] != '\n' && src[line_end] != '\0') line_end++;

    int ln_width = digits_int(err_line);

    fprintf(stderr, BOLD DIM "%*s |\n" RESET, ln_width, "");
    fprintf(stderr, BOLD DIM "%*d | " RESET, ln_width, err_line);
    fwrite(src + line_start, 1, line_end - line_start, stderr);
    fputc('\n', stderr);

    fprintf(stderr, BOLD DIM "%*s | " RESET, ln_width, "");
    size_t caret_col = pos - line_start;
    for (size_t i = 0; i < caret_col; i++) {
        char c = src[line_start + i];
        fputc((c == '\t') ? '\t' : ' ', stderr);
    }
    fprintf(stderr, BOLD RED "^\n" RESET);

    free(src);
    exit(EXIT_FAILURE);
}
