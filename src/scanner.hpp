#pragma once

#include <string>
#include <queue>

class scanner
{
    private:
	using queue = std::queue<std::string>;

	queue& input_queue;
	queue& output_queue;

    public:
	scanner(queue& input_queue, queue& output_queue) :
	    input_queue{input_queue}, output_queue{output_queue} {}

	void run()
	{

	}
};
