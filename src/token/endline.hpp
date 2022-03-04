#pragma once

#include <stdexcept>

#include "../word/word.hpp"

class endline_token 
{
    public:
	endline_token(words word)
	{
	    if(word != words::endline)
		throw std::runtime_error("Wrong word in endline_token");
	}
};
