#include <catch2/catch_test_macros.hpp>

#include "evaluator/evaluator.h"
#include "common/types.h"
#include <string>

TEST_CASE("Calculates result from RPN", "[EvaluateRPN]")
{
    SECTION("Basic addition expression")
    {
        std::vector<Token> rpn = {
            {.symbol = "1", .type = NUMBER},
            {.symbol = "2", .type = NUMBER},
            {.symbol = "+", .type = PLUS},
        };
        double want = 3;
        double got = EvaluateRPN(rpn);
        REQUIRE(want == got);
    }

    SECTION("Basic multiplication expression")
    {
        std::vector<Token> rpn = {
            {.symbol = "2", .type = NUMBER},
            {.symbol = "3", .type = NUMBER},
            {.symbol = "*", .type = MULTIPLY},
        };
        double want = 6;
        double got = EvaluateRPN(rpn);
        REQUIRE(want == got);
    }

    SECTION("Basic minus expression")
    {
        std::vector<Token> rpn = {
            {.symbol = "5.5", .type = NUMBER},
            {.symbol = "2.5", .type = NUMBER},
            {.symbol = "-", .type = MINUS},
        };
        double want = 3;
        double got = EvaluateRPN(rpn);
        REQUIRE(want == got);
    }

    SECTION("Basic parenthesis expression")
    {
        std::vector<Token> rpn = {
            {.symbol = "1", .type = NUMBER},
            {.symbol = "2", .type = NUMBER},
            {.symbol = "+", .type = PLUS},
            {.symbol = "3", .type = NUMBER},
            {.symbol = "*", .type = MULTIPLY},
        };
        double want = 9;
        double got = EvaluateRPN(rpn);
        REQUIRE(want == got);
    }

    SECTION("Division with parenthesis")
    {
        std::vector<Token> rpn = {
            {.symbol = "10", .type = NUMBER},
            {.symbol = "5", .type = NUMBER},
            {.symbol = "3", .type = NUMBER},
            {.symbol = "-", .type = MINUS},
            {.symbol = "/", .type = DIVIDE},
        };
        double want = 5;
        double got = EvaluateRPN(rpn);
        REQUIRE(want == got);
    }

    SECTION("Nested parenthesis")
    {
        std::vector<Token> rpn = {
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
        double want = 38;
        double got = EvaluateRPN(rpn);
        REQUIRE(want == got);
    }

    SECTION("Two separate parenthesis expressions")
    {
        std::vector<Token> rpn = {
            {.symbol = "1", .type = NUMBER},
            {.symbol = "2.5", .type = NUMBER},
            {.symbol = "+", .type = PLUS},
            {.symbol = "3", .type = NUMBER},
            {.symbol = "1", .type = NUMBER},
            {.symbol = "-", .type = MINUS},
            {.symbol = "*", .type = MULTIPLY},
        };
        double want = 7;
        double got = EvaluateRPN(rpn);
        REQUIRE(want == got);
    }

    SECTION("All operators in an expression")
    {
        std::vector<Token> rpn = {
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
        double want = 6.2;
        double got = EvaluateRPN(rpn);
        REQUIRE(want == got);
    }
}