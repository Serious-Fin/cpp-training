#include <iostream>
#include <string>
#include "calculator.h"

int main()
{
    std::string a = "aaa";
    std::cout << Calculator::calculate("2 + 4 * 999 - (8.2 / 4,12)") << "\n";
}