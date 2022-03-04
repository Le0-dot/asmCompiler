#pragma once

#include "../../word/operations.hpp"
#include "../op.hpp"

#include "lexeme/reg.hpp"
#include "lexeme/nums.hpp"

class ldi_op : public op
{
    private:
	reg d;
	num9 s;

    public:
	ldi_op(operations op, reg d, num9 s) :
	    d{d}, s{s}
	{
	    if(op != operations::ldi)
		throw std::runtime_error("Wrong operation in ldi_op");
	}

	virtual uint16_t get_binary()
	{
	    return 0xA << 12 + d.get_binary() << 9 + s.get_binary();
	}
};
