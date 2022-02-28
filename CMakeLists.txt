cmake_minimum_required(VERSION 3.22.2)

project(asmComp)

set(EXECUTABLE_OUTPUT_PATH ./bin)

set(CMAKE_CXX_STANDART 17)
set(CMAKE_CXX_STANDART_REQUIRED ON)

set(SRC src/main.cpp src/scanner.hpp src/parser.hpp)

add_executable(${PROJECT_NAME} ${SRC})
