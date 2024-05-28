#include "../lexer/tokens.hpp"
#include "../parser/AST/ast.hpp"
#include "enviornment/enviornment.hpp"
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Value.h>
#include <llvm/Support/raw_ostream.h>
#include <memory>
#include <string>
#include <unordered_map>


namespace compiler {
class Compiler {
  public:
    llvm::LLVMContext llvm_context;
    std::unique_ptr<llvm::Module> llvm_module;
    llvm::IRBuilder<> llvm_ir_builder; // Move the declaration here
    std::unordered_map<std::string, llvm::Type*> type_map;
    enviornment::Enviornment enviornment;

    Compiler();

    void compile(std::shared_ptr<AST::Node> node);

  private:
    void _visitProgram(std::shared_ptr<AST::Program> program);

    void _visitExpressionStatement(std::shared_ptr<AST::ExpressionStatement> expression_statement);

    std::tuple<llvm::Value*, llvm::Type*> _visitInfixExpression(std::shared_ptr<AST::InfixExpression> infixed_expression);

    void _visitVariableDeclarationStatement(std::shared_ptr<AST::VariableDeclarationStatement> variable_declaration_statement);
    void _visitVariableAssignmentStatement(std::shared_ptr<AST::VariableAssignmentStatement> variable_assignment_statement);

    void _visitFunctionDeclarationStatement(std::shared_ptr<AST::FunctionStatement> function_declaration_statement);
    void _visitReturnStatement(std::shared_ptr<AST::ReturnStatement> return_statement);
    void _visitBlockStatement(std::shared_ptr<AST::BlockStatement> block_statement);

    std::tuple<llvm::Value*, llvm::Type*> _resolveValue(std::shared_ptr<AST::Node> node);
};
} // namespace compiler
