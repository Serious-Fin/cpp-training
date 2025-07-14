#include "tokenizer/tokenizer.h"
#include <vector>
#include "common/types.h"

bool isNumericExpression(char character);
bool isNumber(char character);

std::vector<Token> TokenizeExpression(const std::string &expression)
{
    std::vector<Token> tokens;
    int currIndex = 0;
    while (currIndex < expression.length())
    {
        char character = expression[currIndex];
        switch (character)
        {
        case '+':
            tokens.push_back(Token{
                .symbol = "+",
                .type = PLUS});
            break;

        case '-':
            tokens.push_back(Token{
                .symbol = "-",
                .type = MINUS});
            break;

        case '*':
            tokens.push_back(Token{
                .symbol = "*",
                .type = MULTIPLY});
            break;

        case '/':
            tokens.push_back(Token{
                .symbol = "/",
                .type = DIVIDE});
            break;

        case '(':
            tokens.push_back(Token{
                .symbol = "(",
                .type = L_PAREN});
            break;

        case ')':
            tokens.push_back(Token{
                .symbol = ")",
                .type = R_PAREN});
            break;

        case ' ':
            break;

        default:
            int start, end;
            start = end = currIndex;
            while (isNumericExpression(expression[end]) && end < expression.length())
            {
                end++;
            }
            if (end > start)
            {
                tokens.push_back(Token{
                    .symbol = expression.substr(start, (end - start)),
                    .type = NUMBER});
                currIndex += (end - start - 1);
            }
            else
            {
                std::string errorMessage = std::string("unknown character encountered \"") + character + "\"";
                throw std::invalid_argument(errorMessage);
            }
            break;
        }
        currIndex++;
    }
    return tokens;
}

bool isNumericExpression(char character)
{
    return isNumber(character) || character == '.';
}

bool isNumber(char character)
{
    return character >= '0' && character <= '9';
}