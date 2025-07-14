#include <iostream>
#include <string>
#include "calculator/calculator.h"

int main()
{
    std::cout << Calculator::calculate("5 * 5 + 100 / 7.5 * 8") << "\n";
}

// TODO:
// Add tests DOING
// add proper error handling DOING
// add CLI for main()