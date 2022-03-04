#pragma once

#include <variant>

#include "../../word/operations.hpp"

#include "lexeme/reg.hpp"
#include "lexeme/nums.hpp"

class add_op
{
    private:
	reg d, s1;
	std::variant<reg, num5> s2;

    public:
	add_op(operations op, reg d, reg s1, reg s2) :
	    d{d}, s1{s1}, s2{s2}
	{
	    if(op != operations::add)
		throw std::runtime_error("Wrong operation in add_op");
	}

	add_op(operations op, reg d, reg s1, num5 s2) :
	    d{d}, s1{s1}, s2{s2}
	{
	    if(op != operations::add)
		throw std::runtime_error("Wrong operation in add_op");
	}

	uint16_t get_binary()
	{
	    try {
		return 0x1 << 12 + d.get_binary() << 9 + s1.get_binary() << 6 + std::get<reg>(s2).get_binary();
	    } catch (const std::bad_variant_access&) {
		return 0x1 << 12 + d.get_binary() << 9 + s1.get_binary() << 6 + 1 << 5 +
		    std::get<num5>(s2).get_binary();
	    }
	}
};
