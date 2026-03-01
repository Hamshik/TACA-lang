#include "colors.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
typedef struct {
    char* filename;
    char* source;
}Lexer;

void print_diagnostic(
    Lexer *lexer,
    int err_line,
    int err_col,
    int ini_pos,
    const char *message
){
    const char *filename = lexer->filename;

    int col_start = ini_pos;
    int col_end = ini_pos;
    

    while(lexer->source[col_start] != '\n' && lexer->source[col_start] != '\0')col_start--;  
    while(lexer->source[col_end] != '\n'&& lexer->source[col_end] != '\0') col_end++;
    
    char* spaceBuf = malloc(5);
    if(err_line <= 9)spaceBuf = " ";
    else if(err_line <= 99)spaceBuf = "  ";
    else if(err_line <= 999)spaceBuf = "  ";
    else if(err_line <= 9999)spaceBuf = "   ";
    else if(err_line <= 9999)spaceBuf = "    ";
    else if(err_line <= 99999)spaceBuf = "     ";
    else if(err_line <= 999999)spaceBuf = "     ";
    else if(err_line <= 9999999)spaceBuf = "      ";
    else spaceBuf = " ";

    fprintf(stderr,BOLD RED"%s| error: %s in\n" RESET, spaceBuf, message);
    fprintf(stderr,BOLD RED"%s| -> "RESET, spaceBuf);
    fprintf(stderr,UNDERLINE BOLD DIM BLACK WHITE"%s\n" RESET, filename);
    fprintf(stderr,BOLD RED"%s| at line %d:%d\n" RESET, spaceBuf, err_line, err_col);
    fprintf(stderr,BOLD MAGENTA "%s%c\n" RESET,spaceBuf,'|');
    fprintf(stderr,BOLD MAGENTA "%d|" RESET,err_line);
    for(int i = col_start;i <= col_end;i++){
        char current_char = lexer->source[i];
        if(current_char == '\n') continue;
        fprintf(stderr,BOLD MAGENTA "%c" RESET, current_char);
    }
    fprintf(stderr,BOLD MAGENTA"\n%s|" RESET,spaceBuf);
    for(int i = col_start;i < err_col + col_start; i++){
        char currnt_char = lexer->source[i];
        switch (currnt_char){
            case '\n': continue;
            case '\t':  fputs("\t", stderr); break;
            default:    fputs(" ",stderr); break;
        }
    }
    fputs(BOLD RED"^" RESET, stderr);
    fprintf(stderr,"\n");
    exit(EXIT_FAILURE);
}