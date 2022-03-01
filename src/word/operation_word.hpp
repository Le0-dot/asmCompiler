#pragma once 

#include "word.hpp"

class operation_word : public word
{
    private:
	operations op;

    public:
	operation_word(operations op) : op{op} {}

	virtual words get() { return words::operations; }
	operations get_op() { return op; }
};
