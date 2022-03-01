#pragma once

#include "word.hpp"

class endline_word : public word
{
    public:
	endline_word() = default;

	virtual words get() { return words::endline; }
};
