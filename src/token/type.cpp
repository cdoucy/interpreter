#include <unordered_map>

#include "map.hpp"
#include "token.hpp"

static const std::unordered_map<Token::Type, std::string> tokenTypesString{
    {Token::INTEGER, "int"}
};

static const std::string unknownType{"unknown"};

std::string Token::typeToString(Token::Type type)
{
    const auto &found = umap::get(tokenTypesString, type);

    if (found)
        return found.value();

    return unknownType;
}