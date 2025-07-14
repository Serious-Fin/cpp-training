#include "calculator/calculator.h"
#include <vector>
#include "common/types.h"
#include "tokenizer/tokenizer.h"
#include "rpn_converter/rpn_converter.h"
#include "evaluator/evaluator.h"

double Calculator::calculate(const std::string &expression)
{
    std::vector<Token> test = TokenizeExpression(expression);
    std::vector<Token> rpn = ConvertToRPN(test);
    return EvaluateRPN(rpn);
}
