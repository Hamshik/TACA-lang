#pragma once
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-include-dirs"
#pragma clang diagnostic ignored "-Wunknown-warning-option"

#ifdef __cplusplus
extern "C" {
#endif

#include "utils/colors.h"
#include "utils/error_handler/error.h"

#include "ast/ASTNode.h"

#ifdef __cplusplus
}
#endif
// Utility headers (C++ only)
#include "utils/utf-8_lib/utf8.h"

// Code generation (C++)
#include "codegen/codegen.h"

//libs cpp only
#include "stdlibs/stdlibs.h"

#pragma clang diagnostic pop
