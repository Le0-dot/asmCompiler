#pragma once

#include "../../word/operations.hpp"
#include "../op.hpp"

#include "lexeme/reg.hpp"
#include "lexeme/nums.hpp"

class br_op : public op
{
    private:
	num3 f;
	num9 o;

    public:
	br_op(operations op, num3 f, num9 o) :
	    f{f}, o{o}
	{
	    if(op != operations::br)
		throw std::runtime_error("Wrong operation in br_op");
	}

	virtual uint16_t get_binary()
	{
	    return 0x0 << 12 + f.get_binary() << 9 + o.get_binary();
	}
};
