#include "../colors.h"
#include "error_msg.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

size_t err_no = 0;
size_t warn_no = 0;
bool isError = false;
bool isWarning = false;
bool panic_fatal = true;

static char *read_entire_path(FILE *f, size_t *out_len) {
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

static int starts_with(const char *s, const char *prefix) {
    if (!s || !prefix) return 0;
    while (*prefix) {
        if (*s++ != *prefix++) return 0;
    }
    return 1;
}

void panic(
    file_t *file,
    int err_line,
    int err_col,
    int ini_pos,
    errc_t code,
    const char *detail
){
    const char *filename = (file && file->filename) ? file->filename : "<input>";
    const char *base = errc_msg(code);
    isError = true;
    err_no++;
    size_t src_len = 0;
    char *src = read_entire_path(file->source, &src_len);

    if (detail && *detail) {
        /* Avoid "syntax error: syntax error, unexpected X" style duplication. */
        if (starts_with(detail, base))
            fprintf(stderr, BOLD RED "error[TQ%04d]: %s\n" RESET, (int)code, detail);
        else
            fprintf(stderr, BOLD RED "error[TQ%04d]: %s: %s\n" RESET, (int)code, base, detail);
    } else {
        fprintf(stderr, BOLD RED "error[TQ%04d]: %s\n" RESET, (int)code, base);
    }
    fprintf(stderr, BOLD DIM " --> %s:%d:%d\n" RESET, filename, err_line, err_col);

    if (!src || src_len == 0) {
        free(src);
        fprintf(stderr, BOLD DIM " note:" RESET " could not read source to show caret\n");
        if (panic_fatal) exit(EXIT_FAILURE);
        return;
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
    if (panic_fatal) exit(EXIT_FAILURE);
}
