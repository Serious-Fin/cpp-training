#include <catch2/catch_test_macros.hpp>

#include "rpn_converter/rpn_converter.h"
#include "common/types.h"
#include <string>

TEST_CASE("Expression correctly converted to reverse polish notation", "[ConvertToRPN]")
{
    SECTION("Basic addition expression")
    {
        std::vector<Token> tokens = {
            {.symbol = "1", .type = NUMBER},
            {.symbol = "+", .type = PLUS},
            {.symbol = "2", .type = NUMBER},
        };
        std::vector<Token> want = {
            {.symbol = "1", .type = NUMBER},
            {.symbol = "2", .type = NUMBER},
            {.symbol = "+", .type = PLUS},
        };
        std::vector<Token> got = ConvertToRPN(tokens);
        REQUIRE(want == got);
    }

    SECTION("Basic multiplication expression")
    {
        std::vector<Token> tokens = {
            {.symbol = "2", .type = NUMBER},
            {.symbol = "*", .type = MULTIPLY},
            {.symbol = "3", .type = NUMBER},
        };
        std::vector<Token> want = {
            {.symbol = "2", .type = NUMBER},
            {.symbol = "3", .type = NUMBER},
            {.symbol = "*", .type = MULTIPLY},
        };
        std::vector<Token> got = ConvertToRPN(tokens);
        REQUIRE(want == got);
    }

    SECTION("Basic minus expression")
    {
        std::vector<Token> tokens = {
            {.symbol = "5.5", .type = NUMBER},
            {.symbol = "-", .type = MINUS},
            {.symbol = "2.5", .type = NUMBER},
        };
        std::vector<Token> want = {
            {.symbol = "5.5", .type = NUMBER},
            {.symbol = "2.5", .type = NUMBER},
            {.symbol = "-", .type = MINUS},
        };
        std::vector<Token> got = ConvertToRPN(tokens);
        REQUIRE(want == got);
    }

    SECTION("Basic parenthesis expression")
    {
        std::vector<Token> tokens = {
            {.symbol = "(", .type = L_PAREN},
            {.symbol = "1", .type = NUMBER},
            {.symbol = "+", .type = PLUS},
            {.symbol = "2", .type = NUMBER},
            {.symbol = ")", .type = R_PAREN},
            {.symbol = "*", .type = MULTIPLY},
            {.symbol = "3", .type = NUMBER},
        };
        std::vector<Token> want = {
            {.symbol = "1", .type = NUMBER},
            {.symbol = "2", .type = NUMBER},
            {.symbol = "+", .type = PLUS},
            {.symbol = "3", .type = NUMBER},
            {.symbol = "*", .type = MULTIPLY},
        };
        std::vector<Token> got = ConvertToRPN(tokens);
        REQUIRE(want == got);
    }

    SECTION("Division with parenthesis")
    {
        std::vector<Token> tokens = {
            {.symbol = "10", .type = NUMBER},
            {.symbol = "/", .type = DIVIDE},
            {.symbol = "(", .type = L_PAREN},
            {.symbol = "5", .type = NUMBER},
            {.symbol = "-", .type = MINUS},
            {.symbol = "3", .type = NUMBER},
            {.symbol = ")", .type = R_PAREN},
        };
        std::vector<Token> want = {
            {.symbol = "10", .type = NUMBER},
            {.symbol = "5", .type = NUMBER},
            {.symbol = "3", .type = NUMBER},
            {.symbol = "-", .type = MINUS},
            {.symbol = "/", .type = DIVIDE},
        };
        std::vector<Token> got = ConvertToRPN(tokens);
        REQUIRE(want == got);
    }

    SECTION("Nested parenthesis")
    {
        std::vector<Token> tokens = {
            {.symbol = "2", .type = NUMBER},
            {.symbol = "*", .type = MULTIPLY},
            {.symbol = "(", .type = L_PAREN},
            {.symbol = "3", .type = NUMBER},
            {.symbol = "+", .type = PLUS},
            {.symbol = "4", .type = NUMBER},
            {.symbol = "*", .type = MULTIPLY},
            {.symbol = "(", .type = L_PAREN},
            {.symbol = "5", .type = NUMBER},
            {.symbol = "-", .type = MINUS},
            {.symbol = "1", .type = NUMBER},
            {.symbol = ")", .type = R_PAREN},
            {.symbol = ")", .type = R_PAREN},
        };
        std::vector<Token> want = {
            {.symbol = "2", .type = NUMBER},
            {.symbol = "3", .type = NUMBER},
            {.symbol = "4", .type = NUMBER},
            {.symbol = "5", .type = NUMBER},
            {.symbol = "1", .type = NUMBER},
            {.symbol = "-", .type = MINUS},
            {.symbol = "*", .type = MULTIPLY},
            {.symbol = "+", .type = PLUS},
            {.symbol = "*", .type = MULTIPLY},
        };
        std::vector<Token> got = ConvertToRPN(tokens);
        REQUIRE(want == got);
    }

    SECTION("Two separate parenthesis expressions")
    {
        std::vector<Token> tokens = {
            {.symbol = "(", .type = L_PAREN},
            {.symbol = "1", .type = NUMBER},
            {.symbol = "+", .type = PLUS},
            {.symbol = "2.5", .type = NUMBER},
            {.symbol = ")", .type = R_PAREN},
            {.symbol = "*", .type = MULTIPLY},
            {.symbol = "(", .type = L_PAREN},
            {.symbol = "3", .type = NUMBER},
            {.symbol = "-", .type = MINUS},
            {.symbol = "1", .type = NUMBER},
            {.symbol = ")", .type = R_PAREN},
        };
        std::vector<Token> want = {
            {.symbol = "1", .type = NUMBER},
            {.symbol = "2.5", .type = NUMBER},
            {.symbol = "+", .type = PLUS},
            {.symbol = "3", .type = NUMBER},
            {.symbol = "1", .type = NUMBER},
            {.symbol = "-", .type = MINUS},
            {.symbol = "*", .type = MULTIPLY},
        };
        std::vector<Token> got = ConvertToRPN(tokens);
        REQUIRE(want == got);
    }

    SECTION("All operators in an expression")
    {
        std::vector<Token> tokens = {
            {.symbol = "1", .type = NUMBER},
            {.symbol = "+", .type = PLUS},
            {.symbol = "2", .type = NUMBER},
            {.symbol = "*", .type = MULTIPLY},
            {.symbol = "3", .type = NUMBER},
            {.symbol = "-", .type = MINUS},
            {.symbol = "4", .type = NUMBER},
            {.symbol = "/", .type = DIVIDE},
            {.symbol = "5", .type = NUMBER},
        };
        std::vector<Token> want = {
            {.symbol = "1", .type = NUMBER},
            {.symbol = "2", .type = NUMBER},
            {.symbol = "3", .type = NUMBER},
            {.symbol = "*", .type = MULTIPLY},
            {.symbol = "+", .type = PLUS},
            {.symbol = "4", .type = NUMBER},
            {.symbol = "5", .type = NUMBER},
            {.symbol = "/", .type = DIVIDE},
            {.symbol = "-", .type = MINUS},
        };
        std::vector<Token> got = ConvertToRPN(tokens);
        REQUIRE(want == got);
    }

    SECTION("Missing right parenthesis")
    {
        std::vector<Token> tokens = {
            {.symbol = "(", .type = L_PAREN},
            {.symbol = "1", .type = NUMBER},
            {.symbol = "+", .type = PLUS},
            {.symbol = "2", .type = NUMBER},
        };
        REQUIRE_THROWS_AS(ConvertToRPN(tokens), std::invalid_argument);
    }

    SECTION("Missing left parenthesis")
    {
        std::vector<Token> tokens = {
            {.symbol = "1", .type = NUMBER},
            {.symbol = "+", .type = PLUS},
            {.symbol = "2", .type = NUMBER},
            {.symbol = ")", .type = R_PAREN}};
        REQUIRE_THROWS_AS(ConvertToRPN(tokens), std::invalid_argument);
    }
}