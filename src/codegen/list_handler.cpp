#include "taca.hpp"
#include "codegen/codegen.h"
#include <llvm-22/llvm/IR/Value.h>

static size_t idx = 0;

llvm::Value* generateList(ASTNode_t *n, LLVMContext &ctx, IRBuilder<> &b, IRBuilder<> &entryBuilder, LocalMap &locals) {
    // 1. Determine Type and Size
    // For i32[] n->list.num is the count we calculated in the semantic pass
    Type* elemType = ir_type(n->datatype, ctx);
    ArrayType* arrayType = ArrayType::get(elemType, n->list.num);

    // 2. Allocate the array on the stack
    AllocaInst* arrayPtr = entryBuilder.CreateAlloca(arrayType, nullptr, "list_tmp");

    // 3. Iterate through the AST_SEQ chain
    ASTNode_t* curr = n->list.elements;
    uint32_t index = 0;

    while (curr) {
        // Get the current expression (handle Seq or single element)
        ASTNode_t* exprNode = (curr->kind == AST_SEQ) ? curr->seq.a : curr;

        // Generate IR for the element (this handles things like 4+5 automatically)
        llvm::Value* elementVal = emit_expr(exprNode, ctx, b, entryBuilder, locals);

        // 4. Calculate address: &array[index]
        // Indices are {0, index} - 0 to dereference the pointer, index for the offset
        std::vector<llvm::Value*> indices = {
            entryBuilder.getInt32(0),
            entryBuilder.getInt32(index++)
        };

        llvm::Value* elementAddr = entryBuilder.CreateGEP(arrayType, arrayPtr, indices);

        // 5. Store the value
        entryBuilder.CreateStore(elementVal, elementAddr);

        // Move to next in chain
        if (curr->kind != AST_SEQ) break;
        curr = curr->seq.b;
    }

    return arrayPtr; // Returns the pointer to the start of the array
}

llvm::Value* generateListAccess(ASTNode_t *n, LLVMContext &ctx, IRBuilder<> &b, IRBuilder<> &entryBuilder, LocalMap &locals) {
    // 1. Get the base address of the array
    llvm::Value* arrayPtr = emit_expr(n->index.target, ctx, b, entryBuilder, locals);

    // 2. Get the index value (e.g., the 'i' in list[i])
    llvm::Value* indexVal = emit_expr(n->index.index, ctx, b, entryBuilder, locals);

    // 3. Determine the Element Type
    // You need to pass the actual type of the data inside the array (e.g., i32)
    llvm::Type* elementType = ir_type(n->index.target->ptr_to, ctx);

    // 4. Create the GEP
    // If arrayPtr is an Alloca of [N x i32], use {0, indexVal}
    // If arrayPtr is a raw i32*, use just {indexVal}
    std::vector<llvm::Value*> indices = {
        b.getInt32(0), 
        indexVal      
    };

    // Explicitly pass elementType to CreateGEP
    llvm::Value* elementAddr = b.CreateGEP(arrayPtr->getType()->getScalarType(), arrayPtr, indices);
    
    // 5. Load and return the value
    return b.CreateLoad(elementType, elementAddr, "load_tmp" + idx++);
}