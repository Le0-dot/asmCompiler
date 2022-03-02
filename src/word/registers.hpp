#pragma once

#include <string>
#include <map>

enum class registers {
    R0, R1, R2, R3,
    R4, R5, R6, R7
};

std::string rtos(registers r)
{
    static std::map<registers, std::string> table {
	{ registers::R0, "R0"},
	{ registers::R1, "R1"},
	{ registers::R2, "R2"},
	{ registers::R3, "R3"},
	{ registers::R4, "R4"},
	{ registers::R5, "R5"},
	{ registers::R6, "R6"},
	{ registers::R7, "R7"}
    };
    return table[r];
};

registers ntor(char c)
{
    return static_cast<registers>(c - '0');
}
