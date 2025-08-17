#include <iostream>
#include <string>
#include "calculator/calculator.h"

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cout << "Usage: ./calculator \"<expression>\"\n";
        std::cout << "Example: ./calculator \"(15 / 3) - 2\"\n";
        return 1;
    }
    std::cout << "Result: " << Calculator::calculate(std::string(argv[1])) << "\n";
    return 0;
}
