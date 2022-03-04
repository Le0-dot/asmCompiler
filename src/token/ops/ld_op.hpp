#pragma once

#include "../../word/operations.hpp"

#include "lexeme/reg.hpp"
#include "lexeme/nums.hpp"

class ld_op
{
    private:
	reg d
	num9 s;

    public:
	ld_op(operations op, reg d, num9 s) :
	    d{d}, s{s}
	{
	    if(op != operations::ld)
		throw std::runtime_error("Wrong operation in ld_op");
	}

	uint16_t get_binary()
	{
	    return 0x2 << 12 + d.get_binary() << 9 + s.get_binary();
	}
};
