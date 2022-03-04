#pragma once

#include "../../word/operations.hpp"

#include "lexeme/reg.hpp"
#include "lexeme/nums.hpp"

class jmp_op
{
    private:
	num3 b;

    public:
	jmp_op(operations op, num3 b) :
	    b{b}
	{
	    if(op != operations::jmp)
		throw std::runtime_error("Wrong operation in jmp_op");
	}

	uint16_t get_binary()
	{
	    return 0xC << 12 + b.get_binary() << 6;
	}
};
