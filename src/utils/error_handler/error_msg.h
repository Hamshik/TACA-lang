#ifndef ERROR_MSG_H
#define ERROR_MSG_H

#include <stdio.h>

typedef struct {
    char* filename;
    FILE* source;
}file_t;

extern file_t file;
char *logf_msg(const char *fmt, ...);
void panic(
    file_t *file,
    int err_line,
    int err_col,
    int ini_pos,
    const char *message
);

#endif
