#pragma once

#include <stdexcept>

#include "../../word/operations.hpp"

class halt_op
{
    public:
	halt_op(operations op)
	{
	    if(op != operations::halt)
		throw std::runtime_error("Wrong operation in halt_op");
	}

	uint16_t get_binary()
	{
	    return 0xF << 12 + 0x25;
	}
}
