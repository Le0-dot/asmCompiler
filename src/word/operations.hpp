#pragma once

#include <string>
#include <map>

enum class operations {
    add, and_op, ld, ldi, ldr, lea,
    not_op, st, sti, str, jmp, jsr,
    br, trap, halt
};

std::string otos(operations op)
{
    static std::map<operations, std::string> table {
	{ operations::add, "add"},
	{ operations::and_op, "and"},
	{ operations::ld, "ld"},
	{ operations::ldi, "ldi"},
	{ operations::ldr, "ldr"},
	{ operations::lea, "lea"},
	{ operations::not_op, "not"},
	{ operations::st, "st"},
	{ operations::sti, "sti"},
	{ operations::str, "str"},
	{ operations::jmp, "jmp"},
	{ operations::jsr, "jsr"},
	{ operations::br, "br"},
	{ operations::trap, "trap"},
	{ operations::halt, "halt"}
    };
    return table[op];
}
