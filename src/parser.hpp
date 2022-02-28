#pragma once

#include <string>
#include <queue>

template<typename bits>
class parser
{
    private:
	using iqueue = std::queue<std::string>;
	using oqueue = std::queue<bits>;

	iqueue& input_queue;
	oqueue& output_queue;

    public:
	parser(iqueue& input_queue, oqueue& output_queue) :
	    input_queue{input_queue}, output_queue{output_queue} {}

	void run()
	{

	}
};
