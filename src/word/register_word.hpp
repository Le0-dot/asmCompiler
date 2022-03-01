#pragma once

#include "registers.hpp"

class register_word : public word
{
    private:
	registers reg;

    public:
	register_word(registers reg) : reg{reg} {}

	virtual words get() { return words::registers; }
	registers get_reg() { return reg; }
};
