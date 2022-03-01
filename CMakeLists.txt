cmake_minimum_required(VERSION 3.22.2)

project(asmComp)

set(EXECUTABLE_OUTPUT_PATH ./bin)

set(CMAKE_CXX_STANDART 17)
set(CMAKE_CXX_STANDART_REQUIRED ON)

set(SRC src/main.cpp src/scanner.hpp src/parser.hpp)
set(WORD src/word/word.hpp src/word/operation_word.hpp src/word/register_word.hpp
    src/word/number_word.hpp src/word/operations.hpp src/word/registers.hpp src/word/words.hpp)

add_executable(${PROJECT_NAME} ${SRC} ${WORD})
