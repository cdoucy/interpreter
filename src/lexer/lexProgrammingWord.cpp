#include "lexer.hpp"
#include "map.hpp"

static const std::unordered_map<std::string, Token::Type> keywordsTable{
    {"let", Token::LET},
    {"int", Token::INT},
    {"uint", Token::UINT}
};

bool Lexer::lexProgrammingWord(std::string::const_iterator &begin)
{
    if (!isProgrammingWord(*begin))
        return false;

    auto it = begin;

    for (; isProgrammingWord(*it); ++it);

    std::string lexeme(begin, it);
    Token::Type type = Token::IDENTIFIER;

    auto keywordType = umap::get(keywordsTable, lexeme);
    if (keywordType)
        type = *keywordType;

    this->pushToken(type, lexeme);

    begin = it;

    return true;
}

bool Lexer::isProgrammingWord(char c)
{
    return c == '_' || std::isalnum(c);
}