#pragma once

#include "../../../word/registers.hpp"

class reg
{
    private:
	registers r;

    public:
	reg(registers r) r{r} {}

	uint16_t get_binary() { return static_cast<uint16_t>(r); }
};
