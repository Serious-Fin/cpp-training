#include "evaluator/evaluator.h"
#include <vector>
#include "common/types.h"

double performOperation(int type, double left, double right);

double EvaluateRPN(std::vector<Token> tokens)
{
    std::vector<double> result;
    for (auto &token : tokens)
    {
        if (token.type == NUMBER)
        {
            double number = std::stod(token.symbol, nullptr);
            result.push_back(number);
        }

        if (isOperator(token.type))
        {
            double right = result.back();
            result.pop_back();
            double left = result.back();
            result.pop_back();

            double res = performOperation(token.type, left, right);
            result.push_back(res);
        }
    }
    return result.back();
}

double performOperation(int type, double left, double right)
{
    switch (type)
    {
    case PLUS:
        return left + right;

    case MINUS:
        return left - right;

    case MULTIPLY:
        return left * right;

    case DIVIDE:
        return left / right;

    default:
        // TODO: throw error
        return 0;
    }
}
