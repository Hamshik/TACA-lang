#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

struct file_t {
  FILE *source;
  char *filename;
};

#endif

