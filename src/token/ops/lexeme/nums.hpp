#pragma once

#include <bitset>
#include <cstdint>

template<typename T, size_t N>
class numN
{
    private:
	T val;

    public:
	numN(T val)
	{
	    std::bitset<N> mask;
	    mask = ~mask;
	    this->val = val & mask.to_ulong();
	}
	T get_binary() { return val; } 
};

using num3 = numN<uint16_t, 3>;
using num5 = numN<uint16_t, 5>;
using num6 = numN<uint16_t, 6>;
using num9 = numN<uint16_t, 9>;
using num11 = numN<uint16_t, 11>;
