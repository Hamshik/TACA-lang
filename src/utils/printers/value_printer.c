#include <stdio.h>
#include "value_printer.h"

void print_value(Value value, DataTypes_t datatype) {
    if (datatype == VOID) return;
    printf("Result: ");
    switch (datatype) {
        case I32:      printf("%d\n", value.inum); break;
        case I16:      printf("%hd\n", value.shnum); break;
        case F32:      printf("%f\n", value.fnum); break;
        case F64:      printf("%g\n", value.lfnum); break;
        case BOOL:     printf("%s\n", value.bval ? "true" : "false"); break;
        case STRINGS:  printf("%s\n", value.str ? value.str : ""); break;
        case CHARACTER:printf("%c\n", value.characters); break;
        default:       printf("<unknown>\n"); break;
    }
}
