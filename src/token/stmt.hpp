#pragma once

#include <memory>

#include "op.hpp"
#include "endline.hpp"

class stmt
{
    private:
	std::unique_ptr<op> o;

    public:
	stmt(std::unique_ptr<op>&& o, endline_token) : o{std::move(o)} {}

	uint16_t get_binary() { return o->get_binary(); }
};
