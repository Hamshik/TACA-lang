#include "../../ast/ASTNode.h"
char* get_datatype(DataTypes_t type){
    switch (type)
    {
    case I32: return "I32";
    case I16: return "I16";
    case F32: return "F32";
    case F64: return "F64";
    case STRINGS: return "STRING";
    case CHARACTER: return "CHAR";
    case UNKNOWN: return "UNKNOWN";
    default: return "UNKNOWNS";
    }
}
