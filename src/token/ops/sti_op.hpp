#pragma once

#include "../../word/operations.hpp"

#include "lexeme/reg.hpp"
#include "lexeme/nums.hpp"

class sti_op
{
    private:
	reg d;
	num9 s;

    public:
	sti_op(operations op, reg d, num9 s) :
	    d{d}, s{s}
	{
	    if(op != operations::sti)
		throw std::runtime_error("Wrong operation in sti_op");
	}

	uint16_t get_binary()
	{
	    return 0xB << 12 + d.get_binary() << 9 + s.get_binary();
	}
};
