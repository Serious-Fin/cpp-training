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
// make readme with setup instructions (download catch2 but it's not needed for users idk) and usage instructions