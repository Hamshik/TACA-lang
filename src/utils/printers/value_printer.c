#include <stdio.h>
#include <inttypes.h>
#include "value_printer.h"

static void tq_print_u128(unsigned __int128 x) {
    char buf[64];
    size_t i = 0;
    if (x == 0) {
        putchar('0');
        return;
    }
    while (x > 0 && i < sizeof(buf)) {
        unsigned __int128 q = x / 10;
        unsigned __int128 r = x % 10;
        buf[i++] = (char)('0' + (int)r);
        x = q;
    }
    while (i--) putchar(buf[i]);
}

static void tq_print_i128(__int128 x) {
    if (x < 0) { putchar('-'); tq_print_u128((unsigned __int128)(-x)); return; }
    tq_print_u128((unsigned __int128)x);
}

void print_value(Value value, DataTypes_t datatype) {
    if (datatype == VOID) return;
    printf("Result: ");
    switch (datatype) {
        case I8:      printf("%d\n", (int)value.i8); break;
        case I32:      printf("%d\n", value.inum); break;
        case I16:      printf("%hd\n", value.shnum); break;
        case I128:     tq_print_i128(value.i128); putchar('\n'); break;
        case U8:       printf("%u\n", (unsigned)value.u8); break;
        case U16:      printf("%u\n", (unsigned)value.u16); break;
        case U32:      printf("%" PRIu32 "\n", value.u32); break;
        case U64:      printf("%" PRIu64 "\n", value.u64); break;
        case U128:     tq_print_u128(value.u128); putchar('\n'); break;
        case F32:      printf("%f\n", value.fnum); break;
        case F64:      printf("%g\n", value.lfnum); break;
        case F128:     printf("%Lg\n", value.f128); break;
        case UF32:     printf("%f\n", value.fnum); break;
        case UF64:     printf("%g\n", value.lfnum); break;
        case UF128:    printf("%Lg\n", value.f128); break;
        case BOOL:     printf("%s\n", value.bval ? "true" : "false"); break;
        case STRINGS:  printf("%s\n", value.str ? value.str : ""); break;
        case CHARACTER:printf("%c\n", value.characters); break;
        default:       printf("<unknown>\n"); break;
    }
}
