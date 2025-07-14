#include <catch2/catch_test_macros.hpp>

#include "tokenizer/tokenizer.h"
#include "common/types.h"
#include <string>

TEST_CASE("Expression is tokenized", "[TokenizeExpression]")
{
    SECTION("Parsing expression with spaces")
    {
        std::string expression = "2 + 2 - 7";
        std::vector<Token> want = {
            {.symbol = "2", .type = NUMBER},
            {.symbol = "+", .type = PLUS},
            {.symbol = "2", .type = NUMBER},
            {.symbol = "-", .type = MINUS},
            {.symbol = "7", .type = NUMBER},
        };
        std::vector<Token> got = TokenizeExpression(expression);
        REQUIRE(want == got);
    }

    SECTION("Parsing expression without spaces")
    {
    }

    SECTION("Parsing single digit numbers")
    {
    }

    SECTION("Parsing numbers bigger than 10")
    {
    }

    SECTION("Parsing floating-point numbers")
    {
    }

    SECTION("Parsing parentheses")
    {
    }

    SECTION("Parsing complex expression")
    {
    }

    SECTION("Parsing single character expression")
    {
    }

    SECTION("Parsing empty expression")
    {
    }
}