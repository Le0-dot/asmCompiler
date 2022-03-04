#pragma once

#include "../../word/operations.hpp"

#include "lexeme/reg.hpp"
#include "lexeme/nums.hpp"

class str_op
{
    private:
	reg d;
	num3 b;
	num6 o;

    public:
	str_op(operations op, reg d, num3 b, num6 o) :
	    d{d}, b{b}, o{o}
	{
	    if(op != operations::str)
		throw std::runtime_error("Wrong operation in str_op");
	}

	uint16_t get_binary()
	{
	    return 0x7 << 12 + d.get_binary() << 9 + d.get_binary() << 6 + o.get_binary();
	}
};
