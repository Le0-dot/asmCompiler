#pragma once

#include <stdexcept>

#include "../../word/operations.hpp"
#include "../op.hpp"

class halt_op : public op
{
    public:
	halt_op(operations op)
	{
	    if(op != operations::halt)
		throw std::runtime_error("Wrong operation in halt_op");
	}

	virtual uint16_t get_binary()
	{
	    return 0xf025;
	}
};
