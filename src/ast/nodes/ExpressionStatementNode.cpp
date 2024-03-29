#include "ExpressionStatementNode.hpp"

#include <utility>

ast::ExpressionStatementNode::ExpressionStatementNode(ast::ExpressionNode::ptr expression)
:   _expression(std::move(expression))
{}

void ast::ExpressionStatementNode::accept(ast::IVisitor &visitor)
{
    visitor.visit(*this);
}

const ast::ExpressionNode::ptr &ast::ExpressionStatementNode::getExpression() const
{
    return this->_expression;
}

ast::ExpressionStatementNode::ptr ast::ExpressionStatementNode::create(const ast::ExpressionNode::ptr &expression)
{
    return std::make_shared<ExpressionStatementNode>(expression);
}
