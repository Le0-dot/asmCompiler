#pragma once

#include <string>
#include <map>

enum class traps {
    trp_get_c, trp_out, trp_in,
    trp_put_s, trp_in_u16, trp_out_u16
};

std::string ttos(traps t)
{
    static std::map<traps, std::string> table {
	{ traps::trp_get_c, "trp_get_c" },
	{ traps::trp_out, "trp_out" },
	{ traps::trp_in, "trp_in" },
	{ traps::trp_in_u16, "trp_in_u16" },
	{ traps::trp_out_u16, "trp_out_u16" },
	{ traps::trp_put_s, "trp_put_s" }
    };
    return table[t];
}
