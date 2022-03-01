#pragma once

#include "word.hpp"

template<typename num>
class number_word : public word
{
    private:
	num number;

    public:
	number_word(num number) : number{number} {}

	virtual words get() { return words::numbers; }
	num get_num() { return number; }
};
