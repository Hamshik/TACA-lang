#include "tarkiq.h"
#include "../colors.h"
#include "error_msg.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

size_t err_no = 0;
size_t warn_no = 0;
bool isError = false;
bool isWarning = false;
bool error_fatal = true;


void panic(file_t *file, int err_line, int err_col, int ini_pos, errc_t code, const char *detail)
{
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
        if (error_fatal) exit(EXIT_FAILURE);
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
    if (error_fatal) exit(EXIT_FAILURE);
}

void warn(file_t *file, int warn_line, int warn_col, int ini_pos, warnc_t code, const char *detail)
{
    const char *filename = (file && file->filename) ? file->filename : "<input>";
    const char *base = warnc_msg(code);
    isWarning = true;
    warn_no++;
    size_t src_len = 0;
    char *src = read_entire_path(file->source, &src_len);

    if (detail && *detail) {
        /* Avoid "syntax warning: syntax warning, unexpected X" style duplication. */
        if (starts_with(detail, base))
            fprintf(stderr, BOLD YELLOW "warning[TQ%04d]: %s\n" RESET, (int)code, detail);
        else
            fprintf(stderr, BOLD YELLOW "warning[TQ%04d]: %s: %s\n" RESET, (int)code, base, detail);
    } else {
        fprintf(stderr, BOLD YELLOW "warning[TQ%04d]: %s\n" RESET, (int)code, base);
    }
    fprintf(stderr, BOLD DIM " --> %s:%d:%d\n" RESET, filename, warn_line, warn_col);

    if (!src || src_len == 0) {
        free(src);
        fprintf(stderr, BOLD DIM " note:" RESET " could not read source to show caret\n");
        return;
    }

    size_t pos = (ini_pos < 0) ? 0u : (size_t)ini_pos;
    if (pos >= src_len) pos = src_len - 1;

    size_t line_start = pos;
    while (line_start > 0 && src[line_start - 1] != '\n') line_start--;

    size_t line_end = pos;
    while (line_end < src_len && src[line_end] != '\n' && src[line_end] != '\0') line_end++;

    int ln_width = digits_int(warn_line);

    fprintf(stderr, BOLD DIM "%*s |\n" RESET, ln_width, "");
    fprintf(stderr, BOLD DIM "%*d | " RESET, ln_width, warn_line);
    fwrite(src + line_start, 1, line_end - line_start, stderr);
    fputc('\n', stderr);

    fprintf(stderr, BOLD DIM "%*s | " RESET, ln_width, "");
    size_t caret_col = pos - line_start;
    for (size_t i = 0; i < caret_col; i++) {
        char c = src[line_start + i];
        fputc((c == '\t') ? '\t' : ' ', stderr);
    }
    fprintf(stderr, BOLD YELLOW "^\n" RESET);
    free(src);
}

void syserr(const char *context)
{
    int saved_errno = errno;
    isError = true;
    err_no++;
    fprintf(stderr,BOLD WHITE "Tarkc:" RESET);
    fprintf(stderr, BOLD RED " fatal error:" RESET);
    fprintf(stderr, BOLD WHITE " %s\n" RESET, (context && *context) ? context : "unknown");
    if (saved_errno != 0) {
        fprintf(stderr, BOLD DIM " note:" RESET " %s\n", strerror(saved_errno));
    }
    exit(EXIT_FAILURE);
}

void syswarn(const char *context)
{
    int saved_errno = errno;
    isWarning = true;
    warn_no++;
    fprintf(stderr, BOLD YELLOW "warning[TQ??]: system warning: %s\n" RESET,
            (context && *context) ? context : "unknown");
    if (saved_errno != 0) {
        fprintf(stderr, BOLD DIM " note:" RESET " %s\n", strerror(saved_errno));
    }
}
