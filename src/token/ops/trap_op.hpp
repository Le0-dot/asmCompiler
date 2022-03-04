#pragma once

#include <stdexcept>

#include "../../word/operations.hpp"
#include "lexeme/trapvect.hpp"

class trap_op
{
    private:
	trapvect trp;

    public:
	trap_op(operations op, trapvect trp) : trp{trp}
	{
	    if(op != operations::trap)
		throw std::runtime_error("Wrong operation in trap_op");
	}

	uint16_t get_binary()
	{
	    return 0xF << 12 + trp.get_binary() & 0b1111111; 
	}
}
