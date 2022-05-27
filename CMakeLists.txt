cmake_minimum_required(VERSION 3.22.2)

project(asmCompiler)

set(EXECUTABLE_OUTPUT_PATH ./bin)

set(CMAKE_CXX_STANDART 17)
set(CMAKE_CXX_STANDART_REQUIRED ON)

set(SRC src/main.cpp src/scanner.hpp src/parser.hpp src/utils.hpp src/logging_queue.hpp)
set(WORD src/word/word.hpp src/word/operation_word.hpp src/word/register_word.hpp
    src/word/number_word.hpp src/word/operations.hpp src/word/registers.hpp
    src/word/traps.hpp src/word/trap_word.hpp src/word/endline_word.hpp src/word/words.hpp)
set(TOKEN src/token/stmt.hpp src/token/tokens.hpp src/token/endline.hpp src/token/op.hpp)
set(OPS src/token/ops/add_op.hpp
	src/token/ops/and_op.hpp
	src/token/ops/br_op.hpp
	src/token/ops/halt_op.hpp
	src/token/ops/jmp_op.hpp
	src/token/ops/jsr_op.hpp
	src/token/ops/ld_op.hpp
	src/token/ops/ldi_op.hpp
	src/token/ops/ldr_op.hpp
	src/token/ops/lea_op.hpp
	src/token/ops/not_op.hpp
	src/token/ops/st_op.hpp
	src/token/ops/sti_op.hpp
	src/token/ops/str_op.hpp
	src/token/ops/trap_op.hpp)
set(LEXEME src/token/ops/lexeme/nums.hpp
	   src/token/ops/lexeme/reg.hpp
	   src/token/ops/lexeme/trapvect.hpp)

add_executable(${PROJECT_NAME} ${SRC} ${WORD} ${TOKEN} ${OPS} ${LEXEME})
