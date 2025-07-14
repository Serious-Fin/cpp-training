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
        std::string expression = "2+2-7";
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

    SECTION("Parsing single digit numbers")
    {
        std::string expression = "1 2    3 4  5   6";
        std::vector<Token> want = {
            {.symbol = "1", .type = NUMBER},
            {.symbol = "2", .type = NUMBER},
            {.symbol = "3", .type = NUMBER},
            {.symbol = "4", .type = NUMBER},
            {.symbol = "5", .type = NUMBER},
            {.symbol = "6", .type = NUMBER},
        };
        std::vector<Token> got = TokenizeExpression(expression);
        REQUIRE(want == got);
    }

    SECTION("Parsing numbers bigger than 10")
    {
        std::string expression = "11 203 3113 045 99999999";
        std::vector<Token> want = {
            {.symbol = "11", .type = NUMBER},
            {.symbol = "203", .type = NUMBER},
            {.symbol = "3113", .type = NUMBER},
            {.symbol = "045", .type = NUMBER},
            {.symbol = "99999999", .type = NUMBER},
        };
        std::vector<Token> got = TokenizeExpression(expression);
        REQUIRE(want == got);
    }

    SECTION("Parsing floating-point numbers")
    {
        std::string expression = "1.1 15.99 0.830 0.0001 99999999.9999 1.0";
        std::vector<Token> want = {
            {.symbol = "1.1", .type = NUMBER},
            {.symbol = "15.99", .type = NUMBER},
            {.symbol = "0.830", .type = NUMBER},
            {.symbol = "0.0001", .type = NUMBER},
            {.symbol = "99999999.9999", .type = NUMBER},
            {.symbol = "1.0", .type = NUMBER},
        };
        std::vector<Token> got = TokenizeExpression(expression);
        REQUIRE(want == got);
    }

    SECTION("Parsing parentheses")
    {
        std::string expression = "(())()";
        std::vector<Token> want = {
            {.symbol = "(", .type = L_PAREN},
            {.symbol = "(", .type = L_PAREN},
            {.symbol = ")", .type = R_PAREN},
            {.symbol = ")", .type = R_PAREN},
            {.symbol = "(", .type = L_PAREN},
            {.symbol = ")", .type = R_PAREN},
        };
        std::vector<Token> got = TokenizeExpression(expression);
        REQUIRE(want == got);
    }

    SECTION("Parsing operators")
    {
        std::string expression = "+-*/ * - + /";
        std::vector<Token> want = {
            {.symbol = "+", .type = PLUS},
            {.symbol = "-", .type = MINUS},
            {.symbol = "*", .type = MULTIPLY},
            {.symbol = "/", .type = DIVIDE},
            {.symbol = "*", .type = MULTIPLY},
            {.symbol = "-", .type = MINUS},
            {.symbol = "+", .type = PLUS},
            {.symbol = "/", .type = DIVIDE},
        };
        std::vector<Token> got = TokenizeExpression(expression);
        REQUIRE(want == got);
    }

    SECTION("Parsing single character expression")
    {
        std::string expression = "1";
        std::vector<Token> want = {
            {.symbol = "1", .type = NUMBER},
        };
        std::vector<Token> got = TokenizeExpression(expression);
        REQUIRE(want == got);
    }

    SECTION("Parsing empty expression")
    {
        std::string expression = "";
        std::vector<Token> want = {};
        std::vector<Token> got = TokenizeExpression(expression);
        REQUIRE(want == got);
    }

    SECTION("Encountering an unknown symbol should throw")
    {
        std::string expression = " 22 ? 4";
        REQUIRE_THROWS_AS(TokenizeExpression(expression), std::invalid_argument);
    }
}