#include "calculator.h"
#include <iostream>
#include <vector>

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

std::vector<Token> TokenizeExpression(const std::string &expression);
bool isNumericExpression(char character);
bool isNumber(char character);
bool isSeparator(char character);
std::vector<Token> ConvertToRPN(std::vector<Token> tokens);
bool isOperator(int type);
int getOperatorPriority(int type);
std::vector<Token> ReverseVector(std::vector<Token> list);
double EvaluateRPN(std::vector<Token> tokens);
double performOperation(int type, double left, double right);
void PrintChars(std::vector<Token> tokens, std::string label);

double Calculator::calculate(const std::string &expression)
{
    std::vector<Token> test = TokenizeExpression(expression);
    PrintChars(test, "test set");
    std::vector<Token> rpn = ConvertToRPN(test);
    PrintChars(rpn, "rpn set");

    std::vector<Token> reverse = ReverseVector(rpn);
    return EvaluateRPN(rpn);
}

void PrintChars(std::vector<Token> tokens, std::string label)
{
    std::cout << label << "\n";
    for (auto &t : tokens)
    {
        std::cout << t.symbol << " ";
    }
    std::cout << "\n";
}

// ----- Calculate RPN -----
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
            // pop two operators and perform the thing
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
        std::cout << left << " + " << right << "\n";
        return left + right;

    case MINUS:
        std::cout << left << " - " << right << "\n";
        return left - right;

    case MULTIPLY:
        std::cout << left << " * " << right << "\n";
        return left * right;

    case DIVIDE:
        std::cout << left << " / " << right << "\n";
        return left / right;

    default:
        // TODO: throw error
        return 0;
    }
}

// reverse RPN for faster operations as a stack
std::vector<Token> ReverseVector(std::vector<Token> list)
{
    int start = 0;
    int end = list.size() - 1;
    while (start < end)
    {
        Token tempToken = list[start];
        list[start] = list[end];
        list[end] = tempToken;

        start++;
        end--;
    }
    return list;
}

double CalculateRPN(std::vector<Token> rpn)
{
    while (rpn.size() > 1)
    {
        // get left operand
        Token left = rpn.front();
        Token right = rpn.at(1);
    }
    return 0;
}

// ----- Converter to Reverse Polish Notation -----
std::vector<Token> ConvertToRPN(std::vector<Token> tokens)
{
    std::vector<Token> operatorStack;
    std::vector<Token> output;

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
            while (operatorStack.size() > 0 && operatorStack.back().type != L_PAREN)
            {
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
        if (oper.type != L_PAREN || oper.type != R_PAREN)
        {
            output.push_back(oper);
        }
    }
    return output;
}

bool isOperator(int type)
{
    return type == PLUS || type == MINUS || type == MULTIPLY || type == DIVIDE;
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
        return -1;
    }
}

// ----- Tokenizer -----
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
            break;
        }
        currIndex++;
    }
    std::cout << "\n";
    return tokens;
}

bool isNumericExpression(char character)
{
    return isNumber(character) || isSeparator(character);
}

bool isNumber(char character)
{
    return character >= '0' && character <= '9';
}

bool isSeparator(char character)
{
    return character == '.' || character == ',';
}