#pragma once

#include <queue>

#include "operations.hpp"

class scanner
{
    private:
	using iqueue = std::queue<char>;
	using oqueue = std::queue<operations>;

	iqueue& input_queue;
	oqueue& output_queue;

    public:
	scanner(iqueue& input_queue, oqueue& output_queue) :
	    input_queue{input_queue}, output_queue{output_queue} {}

	void run()
	{

	}
};
