#include <stdint.h>
#include "codegen.h"

int utf8_decode(const unsigned char *s, uint32_t *out) {
    if (!s || !out) return 0;

    if (s[0] < 0x80) {
        *out = s[0];
        return 1;
    }
    else if ((s[0] & 0xE0) == 0xC0) {
        *out = ((s[0] & 0x1F) << 6) |
               (s[1] & 0x3F);
        return 2;
    }
    else if ((s[0] & 0xF0) == 0xE0) {
        *out = ((s[0] & 0x0F) << 12) |
               ((s[1] & 0x3F) << 6) |
               (s[2] & 0x3F);
        return 3;
    }
    else if ((s[0] & 0xF8) == 0xF0) {
        *out = ((s[0] & 0x07) << 18) |
               ((s[1] & 0x3F) << 12) |
               ((s[2] & 0x3F) << 6) |
               (s[3] & 0x3F);
        return 4;
    }

    return -1; // invalid UTF-8
}