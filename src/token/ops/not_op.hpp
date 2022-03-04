#pragma once

#include "../../word/operations.hpp"

#include "lexeme/reg.hpp"
#include "lexeme/nums.hpp"

class not_op
{
    private:
	reg d, s;

    public:
	not_op(operations op, reg d, reg s) :
	    d{d}, s{s}
	{
	    if(op != operations::not_op)
		throw std::runtime_error("Wrong operation in not_op");
	}

	uint16_t get_binary()
	{
	    return 0x9 << 12 + d.get_binary() << 9 + s.get_binary() << 6;
	}
};
