#include "rpn_converter.h"
#include <vector>
#include "common/types.h"

int getOperatorPriority(int type);

std::vector<Token> ConvertToRPN(std::vector<Token> tokens)
{
    std::vector<Token> operatorStack;
    std::vector<Token> output;

    // Shunting yard algorithm
    for (auto &token : tokens)
    {
        if (token.type == NUMBER)
        {
            output.push_back(token);
        }

        if (isOperator(token.type))
        {
            while (operatorStack.size() > 0 && operatorStack.back().type != L_PAREN && getOperatorPriority(operatorStack.back().type) >= getOperatorPriority(token.type))
            {
                Token poppedOperator = operatorStack.back();
                operatorStack.pop_back();
                output.push_back(poppedOperator);
            }
            operatorStack.push_back(token);
        }

        if (token.type == L_PAREN)
        {
            operatorStack.push_back(token);
        }

        if (token.type == R_PAREN)
        {
            while (true)
            {
                if (operatorStack.size() == 0)
                {
                    throw std::invalid_argument("Mismatched parenthesis in the expression");
                }
                if (operatorStack.back().type == L_PAREN)
                {
                    break;
                }
                Token poppedOperator = operatorStack.back();
                operatorStack.pop_back();
                output.push_back(poppedOperator);
            }
            operatorStack.pop_back();
        }
    }

    while (operatorStack.size() > 0)
    {
        Token oper = operatorStack.back();
        operatorStack.pop_back();
        if (oper.type == L_PAREN)
        {
            throw std::invalid_argument("Mismatched parenthesis in the expression");
        }
        output.push_back(oper);
    }
    return output;
}

int getOperatorPriority(int type)
{
    switch (type)
    {
    case PLUS:
        return 2;

    case MINUS:
        return 2;

    case MULTIPLY:
        return 3;

    case DIVIDE:
        return 3;

    default:
        throw std::invalid_argument("Unknown operator");
    }
}