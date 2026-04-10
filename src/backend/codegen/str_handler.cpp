#include "../utils/utf-8_lib/utf8/unchecked.h"
#include "codegen.h"
#include <stdint.h>
#include <cstring>

uint32_t decode_utf8(const char* raw, size_t raw_len, size_t* byte_len, Utf8Error* error) {
    if (!raw || raw_len == 0) {
        *error = Utf8Error::Empty;
        return 0;
    }

    const char* it  = raw;
    const char* end = raw + raw_len;

    // 1. Validation check (since we can't use exceptions)
    if (utf8::find_invalid(it, end) != end) {
        *error = Utf8Error::InvalidUtf8;
        return 0;
    }

    // 2. Decode the first character (unchecked assumes prior validation)
    uint32_t cp = utf8::unchecked::next(it);
    *byte_len = (size_t)(it - raw);

    // 3. Safety Net: If it's not the end of the string, it's a multi-char literal
    if (it != end) {
        *error = Utf8Error::MultiCharacter;
        return 0;
    }

    *error = Utf8Error::None;
    return cp;
}
