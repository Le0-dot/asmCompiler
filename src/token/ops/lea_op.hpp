#pragma once

#include "../../word/operations.hpp"

#include "lexeme/reg.hpp"
#include "lexeme/nums.hpp"

class lea_op
{
    private:
	reg d
	num9 s;

    public:
	lea_op(operations op, reg d, num9 s) :
	    d{d}, s{s}
	{
	    if(op != operations::lea)
		throw std::runtime_error("Wrong operation in lea_op");
	}

	uint16_t get_binary()
	{
	    return 0xE << 12 + d.get_binary() << 9 + s.get_binary();
	}
};
