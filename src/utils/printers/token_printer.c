#include "../../ast/ASTNode.h"
char* get_datatype(DataTypes_t type){
    switch (type)
    {
    case INT: return "INT";
    case SHORT: return "SHORT";
    case FLOAT: return "FLOAT";
    case DOUBLE: return "DOUBLE";
    case STRINGS: return "STRING";
    case CHARACTER: return "CHAR";
    case UNKNOWN: return "UNKNOWN";
    default: return "UNKNOWNS";
    }
}