#pragma once

#include "word.hpp"
#include "traps.hpp"

class trap_word : public word
{
    private:
	const traps trap;
    
    public:
	trap_word(traps trap) : trap{trap} {}

	virtual words get() { return words::traps; }
	traps get_trp() { return trap; }
};
