#pragma once

#include <iostream>

#include "IVisitor.hpp"
#include "IntegerNode.hpp"
#include "StringNode.hpp"
#include "BinaryNode.hpp"
#include "ExpressionNode.hpp"
#include "UnaryNode.hpp"
#include "LogicalNode.hpp"
#include "IdentifierNode.hpp"

#include "ExpressionStatementNode.hpp"
#include "DeclarationNode.hpp"
#include "AssignmentNode.hpp"
#include "PrintNode.hpp"
#include "BlockNode.hpp"
#include "WhileNode.hpp"
#include "ConditionNode.hpp"
#include "ForNode.hpp"

#include "ProgramNode.hpp"

#include "State.hpp"
#include "Object.hpp"

namespace ast
{
    class EvalVisitor final : public IVisitor
    {
        public:
            explicit EvalVisitor(std::ostream &output = std::cout);
            ~EvalVisitor() final = default;

            void visit(IntegerNode &node) final;
            void visit(StringNode &node) final;
            void visit(BinaryNode &node) final;
            void visit(UnaryNode &node) final;
            void visit(LogicalNode &node) final;
            void visit(IdentifierNode &node) final;

            void visit(ExpressionStatementNode &node) final;
            void visit(DeclarationNode &node) final;
            void visit(AssignmentNode &node) final;
            void visit(PrintNode &node) final;
            void visit(BlockNode &node) final;
            void visit(WhileNode &node) final;
            void visit(ConditionNode &node) final;
            void visit(ForNode &node) final;

            void visit(ProgramNode &node) final;

            const runtime::Object &value() const noexcept;
            [[nodiscard]] Token::Integer getResult() const;

            const runtime::State &getState() const noexcept;

            void clearState() noexcept;

        private:
            std::ostream &_output;
            runtime::Object _expressionResult;
            runtime::State::ptr _state;

            const runtime::Object &evaluate(const ast::ExpressionNode::ptr &expr);

    };
};