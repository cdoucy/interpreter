#pragma once

#include "ast.hpp"
#include "lexer.hpp"

class Parser
{
    public:
        Parser() = default;
        ~Parser() = default;

        void feed(const std::string &expression);

        [[nodiscard]] const ast::INode::ptr &getAstRoot() const noexcept;

        void clear() noexcept;


    private:
        Lexer _lexer;
        ast::INode::ptr _astRoot;
        Token::Iterator _tokenItr;

        ast::ProgramNode::ptr parseProgram();
        ast::StatementNode::ptr parseStatement();
        ast::StatementNode::ptr parseExpressionStatement();
        ast::StatementNode::ptr parseDeclarationStatement();
        ast::StatementNode::ptr parseAssignmentStatement();
        ast::StatementNode::ptr parseIncrementStatement();
        ast::StatementNode::ptr parseReturnStatement();
        ast::StatementNode::ptr parseBreakStatement();
        ast::StatementNode::ptr parseContinueStatement();
        ast::DeclarationNode::ptr parseDeclaration();
        ast::AssignmentNode::ptr parseAssignment();
        ast::IncrementNode::ptr parseIncrement();
        ast::StatementNode::ptr parseReturn();
        ast::StatementNode::ptr parsePrint();
        ast::StatementNode::ptr parseBlockStatement();
        ast::BlockNode::ptr parseBlock();
        ast::StatementNode::ptr parseWhile();
        ast::StatementNode::ptr parseFor();
        ast::StatementNode::ptr parseFunction();
        ast::InitStatementNode::ptr parseInitStatement();
        ast::StepStatementNode::ptr parseStepStatement();
        ast::StatementNode::ptr parseConditions();
        ast::ExpressionNode::ptr parseExpression();
        ast::ExpressionNode::ptr parseLogicalOr();
        ast::ExpressionNode::ptr parseLogicalAnd();
        ast::ExpressionNode::ptr parseBitwiseOr();
        ast::ExpressionNode::ptr parseBitwiseXor();
        ast::ExpressionNode::ptr parseBitwiseAnd();
        ast::ExpressionNode::ptr parseEquality();
        ast::ExpressionNode::ptr parseComparison();
        ast::ExpressionNode::ptr parseBitshift();
        ast::ExpressionNode::ptr parseTerm();
        ast::ExpressionNode::ptr parseFactor();
        ast::ExpressionNode::ptr parseUnary();
        ast::ExpressionNode::ptr parseCall();
        std::vector<ast::ExpressionNode::ptr> parseParams();
        ast::ExpressionNode::ptr parsePrimary();
        ast::ExpressionNode::ptr parseInteger();
        ast::ExpressionNode::ptr parseString();
        ast::ExpressionNode::ptr parseIdentifier();
        ast::ExpressionNode::ptr parseGrouping();

        using ParseFunction = std::function<ast::ExpressionNode::ptr ()>;

        ast::ExpressionNode::ptr parseBinaryExpression(
            const std::initializer_list<Token::Type> &matchTokens,
            const ParseFunction &parseSubExpression,
            bool logical = false
        );

        ast::ExpressionNode::ptr parseParenthesizedExpression(const Token &previousToken);

        std::optional<std::pair<std::string, Token::Type>> parseTypeIdent();

        static SyntaxError syntaxError(const std::string &errorMessage, const Token &token);
};