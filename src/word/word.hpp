#pragma once

#include <string>

#include "operations.hpp"
#include "registers.hpp"

enum class words {
    operations, registers, numbers, endline
};

class word 
{
    public:
	word() = default;
	~word() = default;

	word(word&) = delete;
	word(word&&) = delete;
	word& operator=(word&) = delete;
	word& operator=(word&&) = delete;

	virtual words get() = 0;
};
