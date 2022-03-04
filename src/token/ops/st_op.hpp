#pragma once

#include "../../word/operations.hpp"

#include "lexeme/reg.hpp"
#include "lexeme/nums.hpp"

class st_op
{
    private:
	reg d;
	num9 s;

    public:
	st_op(operations op, reg d, num9 s) :
	    d{d}, s{s}
	{
	    if(op != operations::st)
		throw std::runtime_error("Wrong operation in st_op");
	}

	uint16_t get_binary()
	{
	    return 0x3 << 12 + d.get_binary() << 9 + s.get_binary();
	}
};
