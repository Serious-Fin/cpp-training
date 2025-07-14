#include "common/types.h"

bool isOperator(int type)
{
    return type == PLUS || type == MINUS || type == MULTIPLY || type == DIVIDE;
}