#pragma once

#include <variant>

#include "../../word/operations.hpp"
#include "../op.hpp"

#include "lexeme/reg.hpp"
#include "lexeme/nums.hpp"

class jsr_op : public op
{
    private:
	std::variant<num3, num11> s;

    public:
	jsr_op(operations op, num3 s) :
	    s{s}
	{
	    if(op != operations::jsr)
		throw std::runtime_error("Wrong operation in jsr_op");
	}

	jsr_op(operations op, num11 s) :
	    s{s}
	{
	    if(op != operations::jsr)
		throw std::runtime_error("Wrong operation in jsr_op");
	}

	virtual uint16_t get_binary()
	{
	    try {
		return 0x4 << 12 + 1 << 11 + std::get<num11>(s).get_binary();
	    } catch (const std::bad_variant_access&) {
		return 0x4 << 12 + std::get<num3>(s).get_binary() << 6;
	    }
	}
};
