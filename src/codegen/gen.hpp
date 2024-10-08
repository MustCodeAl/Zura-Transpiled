#pragma once

#include "../ast/expr.hpp"
#include "../ast/stmt.hpp"
#include "../ast/types.hpp"
#include "optimize.hpp"

#include <string>
#include <unordered_map>
#include <vector>

namespace codegen {

using StmtHandler = std::function<void(Node::Stmt *)>;
using ExprHandler = std::function<void(Node::Expr *)>;
using TypeHandler = std::function<void(Node::Type *)>;

inline std::unordered_map<NodeKind, TypeHandler> typeHandlers;
inline std::unordered_map<NodeKind, StmtHandler> stmtHandlers;
inline std::unordered_map<NodeKind, ExprHandler> exprHandlers;


template <typename T, typename U>
T lookup(const std::unordered_map<U, T> &map, U key) {
    auto iter = map.find(key);
    if (iter == map.end()) {
        return nullptr;
    }
    return iter->second;
}

void initMaps();

inline std::unordered_map<std::string, size_t> stackTable = {};
inline size_t stackSize;

void visitStmt(Node::Stmt *stmt);
void visitExpr(Node::Expr *expr);

void symbolType(Node::Type *type);
void arrayType(Node::Type *type);
void pointerType(Node::Type *type);

void program(Node::Stmt *stmt);
void constDecl(Node::Stmt *stmt);
void funcDecl(Node::Stmt *stmt);
void varDecl(Node::Stmt *stmt);
void block(Node::Stmt *stmt);
void ifStmt(Node::Stmt *stmt);
void print(Node::Stmt *stmt);
void expr(Node::Stmt *stmt);
void _return(Node::Stmt *stmt);

void binary(Node::Expr *expr);
void grouping(Node::Expr *expr);
void unary(Node::Expr *expr);
void call(Node::Expr *expr);
void ternary(Node::Expr *expr);
void assign(Node::Expr *expr);
void primary(Node::Expr *expr);

// assembly
enum class Section {
    // section .text
    Main, // main function
    Head, // user functions
    // section .data
    Data, // strings, constants
};

enum class NativeASMFunc {
    strlen
};

inline std::vector<Instr> text_section = {};
inline std::vector<Instr> head_section = {};
inline std::vector<Instr> data_section = {}; // Technically, this will just be either Label or DBInstr

inline std::unordered_map<NativeASMFunc, bool> nativeFunctionsUsed = {};

inline bool isEntryPoint = false;
inline size_t conditionalCount = 0;
inline size_t stringCount = 0;
inline size_t loopCount = 0;

void push(Instr instr, Section section = Section::Main);

void pushCompAsExpr(); // assuming compexpr's will already do the "cmp" and "jmp", we will push 0x0 or 0x1 depending on the result

void gen(Node::Stmt *stmt, bool isSaved, std::string output);
} // namespace codegen
