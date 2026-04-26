// runtime.c
#include <stdlib.h>
#include <string.h>

char* tq_concat(char* a, char* b) {
    size_t lenA = strlen(a);
    size_t lenB = strlen(b);

    char* res = (char*)malloc(lenA + lenB + 1);

    memcpy(res, a, lenA);
    memcpy(res + lenA, b, lenB);

    res[lenA + lenB] = '\0';
    return res;
}
