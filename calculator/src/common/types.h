#ifndef COMMON_TYPES_H
#define COMMON_TYPES_H

#include <ostream>
#include <string>

enum
{
    NUMBER,
    PLUS,
    MINUS,
    MULTIPLY,
    DIVIDE,
    L_PAREN,
    R_PAREN
};

struct Token
{
    std::string symbol;
    int type;

    bool operator==(const Token &other) const
    {
        return symbol == other.symbol && type == other.type;
    }
};

bool isOperator(int type);
std::ostream &operator<<(std::ostream &os, Token const &value);

#endif