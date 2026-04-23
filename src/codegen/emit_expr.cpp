#include "../taca.hpp"
#include "utils/error_handler/error.h"
#include "llvm/IR/GlobalValue.h"
#include "llvm/IR/GlobalVariable.h"
#include "llvm/IR/Value.h"
#include <codecvt>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <vector>

llvm::Value *emit_expr(ASTNode_t *n, LLVMContext &ctx, IRBuilder<> &b,
                       IRBuilder<> &entryBuilder, LocalMap &locals) {
  if (!n)
    return nullptr;
  if (blockTerminated(b))
    return nullptr;

  switch (n->kind) {
  case AST_FN:
    // function bodies handled separately
    return nullptr;
  case AST_NUM:
    return emit_number(n, ctx);
  case AST_BOOL:
    return ConstantInt::get(Type::getInt1Ty(ctx), n->datatype == BOOL ? 1 : 0);
  case AST_STR:
    return b.CreateGlobalString(n->literal.raw ? n->literal.raw : "", "strlit");

  case AST_CHAR: {
    if (!n->literal.raw) {
      error(&file, n->line, n->col, n->pos, INVAILD_UTF8_CHAR, nullptr);
      return nullptr;
    }

    size_t len = 0;
    Utf8Error err = Utf8Error::None;
    uint32_t codepoint = decode_utf8(n->literal.raw, n->literal.len, &len, &err);

    // Error Handling
    if (err != Utf8Error::None) {
      const char *msg = nullptr;
      if (err == Utf8Error::MultiCharacter)
        msg = "Character literal must be a single UTF-8 character (e.g., 'a' or 'π')";
      else if (err == Utf8Error::Empty)
        msg = "Character literal cannot be empty";

      else if (err == Utf8Error::InvalidUtf8)
        msg = n->literal.raw;

      error(&file, n->line, n->col, n->pos, INVAILD_UTF8_CHAR, msg ? msg : "unknown");
      return nullptr;
    }

    // This now receives a single uint32_t, which LLVM ConstantInt accepts
    return ConstantInt::get(ir_type(CHARACTER, ctx), codepoint);
  }

  case AST_VAR: {
    auto it = locals.find(n->var ? n->var : "");
    if (it != locals.end())
      return b.CreateLoad(ir_type(n->datatype, ctx), it->second, n->var);
    // fallback to module global
    Module *m = b.GetInsertBlock()->getModule();
    auto *g = m->getGlobalVariable(n->var ? n->var : "", true);
    if (g) {
      return b.CreateLoad(ir_type(n->datatype, ctx), g, n->var);
    }
    return nullptr;
  }

  case AST_UNOP:
    return emit_unop(n, ctx, b, entryBuilder, locals);
  case AST_BINOP:
    return emit_binop(n, ctx, b, entryBuilder, locals);

  case AST_ASSIGN:
    return emit_assing(n, ctx, b, entryBuilder, locals);

  case AST_CALL:
    return emit_call(n, ctx, b, entryBuilder, locals);

  case AST_WHILE:
    return emit_whileloop(n, ctx, b, entryBuilder, locals);
  case NODE_FOR:
    return emit_forloops(n, ctx, b, entryBuilder, locals);

  case NODE_IF:
    return emit_if(n, ctx, b, entryBuilder, locals);
  case AST_SEQ: {
    emit_expr(n->seq.a, ctx, b, entryBuilder, locals);

    // 🔥 STOP if block already terminated
    if (blockTerminated(b))
      return nullptr;

    return emit_expr(n->seq.b, ctx, b, entryBuilder, locals);
  }

  case AST_RETURN: {
    llvm::Value *v = emit_expr(n->ret_stmt.value, ctx, b, entryBuilder, locals);

    if (!blockTerminated(b)) {
      if (v)
        b.CreateRet(v);
      else
        b.CreateRetVoid();
    }
    return v;
  }

  default:
    return nullptr;
  }
}
