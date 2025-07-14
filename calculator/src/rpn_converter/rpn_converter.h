
#ifndef RPN_CONVERTER_H
#define RPN_CONVERTER_H

#include <vector>
#include "common/types.h"

std::vector<Token> ConvertToRPN(std::vector<Token> tokens);

#endif