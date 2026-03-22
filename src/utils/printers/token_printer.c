#include "../../ast/ASTNode.h"
char* get_datatype(DataTypes_t type){
    switch (type)
    {
    case I8: return "I8";
    case I32: return "I32";
    case I16: return "I16";
    case I128: return "I128";
    case F32: return "F32";
    case F64: return "F64";
    case F128: return "F128";
    case UF32: return "UF32";
    case UF64: return "UF64";
    case UF128: return "UF128";
    case U8: return "U8";
    case U16: return "U16";
    case U32: return "U32";
    case U64: return "U64";
    case U128: return "U128";
    case BOOL: return "BOOL";
    case STRINGS: return "STRING";
    case CHARACTER: return "CHAR";
    case VOID: return "VOID";
    case UNKNOWN: return "UNKNOWN";
    default: return "UNKNOWNS";
    }
}
