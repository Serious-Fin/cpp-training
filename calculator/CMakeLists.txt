cmake_minimum_required(VERSION 4.0)

project(CalculatorApp LANGUAGES CXX)

set(SOURCE_FILES
    src/main.cpp
    src/tokenizer/tokenizer.cpp
    src/rpn_converter/rpn_converter.cpp
    src/evaluator/evaluator.cpp
)

add_executable(CalculatorApp ${SOURCE_FILES})

target_include_directories(CalculatorApp PRIVATE
    "${CMAKE_SOURCE_DIR}/src"
)