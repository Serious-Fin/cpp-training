cmake_minimum_required(VERSION 4.0)

# ---- Main App Executable ----

project(CalculatorApp LANGUAGES CXX)

set(APP_SOURCE_FILES
    src/calculator/calculator.cpp
    src/tokenizer/tokenizer.cpp
    src/rpn_converter/rpn_converter.cpp
    src/evaluator/evaluator.cpp
    src/common/types.cpp
)

add_executable(CalculatorApp 
    src/main.cpp
    ${APP_SOURCE_FILES}
)

target_include_directories(CalculatorApp PRIVATE
    "${CMAKE_SOURCE_DIR}/src"
)

# ---- Testing Executable ----

add_subdirectory(libs/Catch2)

add_executable(CalculatorTests 
    tests/tokenizer_tests.cpp
    tests/rpn_evaluator_tests.cpp
    ${APP_SOURCE_FILES}
)

target_include_directories(CalculatorTests PRIVATE
    "${CMAKE_SOURCE_DIR}/src"
    "${CMAKE_SOURCE_DIR}/tests"
)

target_link_libraries(CalculatorTests PRIVATE 
    Catch2::Catch2WithMain
)
