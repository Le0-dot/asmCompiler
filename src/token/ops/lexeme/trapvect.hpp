#pragma once

#include <cstdint>
#include <map>

#include "../../../word/traps.hpp"

class trapvect
{
    private:
	const traps trap;
	static map<traps, uint16_t> table;

    public:
	trapvect(traps trap) : trap{trap} {}

	uint16_t get_binary() { return table[trap]; }
};

map<traps, uint16_t> trapvect::table = {
    { traps::trp_get_c, 0x20 },
    { traps::trp_out, 0x21 },
    { traps::trp_put_s, 0x22 },
    { traps::trp_in, 0x23 },
    { traps::trp_in_u16, 0x26 },
    { traps::trp_out_u16, 0x27 }
};
