#pragma once

#include <cstdint>
#include <queue>
#include <memory>
#include <string>
#include <any>
#include <initializer_list>
#include <optional>

#include <fmt/format.h>

#include "InterpreterError.hpp"

class Token
{
    public:
        enum Type : uint8_t
        {
            // Operators
            OPEN_PARENTHESIS, CLOSE_PARENTHESIS,
            OPEN_BRACKET, CLOSE_BRACKET,
            OPEN_SQ_BRACKET, CLOSE_SQ_BRACKET,
            MOD, DIV, MULT,
            PLUS, MINUS,
            GT, GTE, LT, LTE,
            EQUAL, NOT_EQUAL,
            ASSIGN, NOT,
            AND, OR,
            BITWISE_AND, BITWISE_OR, BITWISE_XOR, BITWISE_NOT,
            BITWISE_RSHIFT, BITWISE_LSHIFT,
            SEMICOLON,
            INCR, DECR,
            PLUS_GN, MINUS_GN, MULT_GN, DIV_GN, MOD_GN,
            COMMA,

            // Literal types
            INTEGER, STRING,

            // Keywords
            INT_TYPE, STR_TYPE, VOID_TYPE, FNC_TYPE,

            PRINT,

            WHILE,
            IF, ELSE,
            FOR,
            FNC, RETURN,
            BREAK, CONTINUE,

            // Identifier
            IDENTIFIER
        };

        using Integer = int;
        using String = std::string;

    public:
        using ptr = std::shared_ptr<Token>;

        static ptr create(Token::Type type, const std::string &lexeme, std::size_t line, std::size_t column);

        Token(Token::Type type, const std::string &lexeme, std::size_t line = 0, std::size_t column = 0);

        [[nodiscard]] Type getType() const noexcept;

        [[nodiscard]] bool isType(Token::Type type) const noexcept;
        [[nodiscard]] bool isTypeAnyOf(const std::initializer_list<Token::Type> &types);

        [[nodiscard]] static bool isTypeAnyOf(Token::Type type, const std::initializer_list<Token::Type> &types);

        static std::string typeToString(Type type);

        template<typename T>
        [[nodiscard]] T getLiteral() const
        {
            try {
                return std::any_cast<T>(this->_literalValue);
            } catch (const std::bad_any_cast &err) {
                throw InternalError(fmt::format("mismatched types : {}", err.what()));
            }
        }
        [[nodiscard]] Integer getIntegerLiteral() const;

        [[nodiscard]] const std::string &getLexeme() const noexcept;
        [[nodiscard]] std::size_t getLine() const noexcept;
        [[nodiscard]] std::size_t getColumn() const noexcept;


        bool operator==(const Token &other) const;

        bool isAssignableOperator() const noexcept;
        static bool isAssignableOperator(Token::Type type) noexcept;

    private:
        Type _type;
        std::string _lexeme;
        std::any _literalValue;
        std::size_t _line;
        std::size_t _column;

        static std::any literalFromLexeme(Token::Type type, const std::string &lexeme);
        static Integer integerFromLexeme(const std::string &lexeme);
        static String stringFromLexeme(const std::string &lexeme);

    public:
        using queue = std::queue<ptr>;

        class Iterator
        {
            public:
                Iterator() = default;
                Iterator(Token::queue tokens);
                ~Iterator() = default;

                Iterator &reset(Token::queue &tokens);

                [[nodiscard]] std::optional<Token> get() const noexcept;
                [[nodiscard]] std::optional<Token> next() const noexcept;
                [[nodiscard]] std::optional<Token> prev() const noexcept;

                Iterator &advance();


            private:
                Token::queue _tokens;
                Token::ptr _current;
                Token::ptr _prev;
        };
};