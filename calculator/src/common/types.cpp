#include "common/types.h"
#include <ostream>
#include <string>

bool isOperator(int type)
{
    return type == PLUS || type == MINUS || type == MULTIPLY || type == DIVIDE;
}

std::ostream &operator<<(std::ostream &os, Token const &value)
{
    os << value.symbol;
    return os;
}