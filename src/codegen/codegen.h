#ifndef CODEGEN_H
#define CODEGEN_H

#ifdef __cplusplus
extern "C" {
#endif
#include "../ast/ASTNode.h"
#include "../utils/error_handler/error_msg.h"
#include "../eval/eval.h"

extern file_t file;
int codegen(ASTNode_t* root);
unsigned __int128 tq_parse_u128(const char *s, int *ok);
__int128         tq_parse_i128(const char *s, int *ok);
void panic(file_t *file, int line, int col, int pos, errc_t code, const char *detail);

#ifdef __cplusplus
}
#endif

#endif // CODEGEN_H
