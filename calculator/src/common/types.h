#ifndef COMMON_TYPES_H
#define COMMON_TYPES_H

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
};

bool isOperator(int type);

#endif