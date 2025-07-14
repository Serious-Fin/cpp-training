#include <iostream>
#include <string>
#include "calculator/calculator.h"

int main()
{
    std::cout << Calculator::calculate("5 * 5 + 100 / 7.5 * 8") << "\n";
}

// TODO:
// Add tests
// Move out tokenizer, evaluater and calculator to separate projects as in best practices
// add proper error handling