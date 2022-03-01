#pragma once

#include <string>

class word 
{
    public:
	word() = default;
	~word() = default;

	word(word&) = delete;
	word(word&&) = delete;
	word& operator=(word&) = delete;
	word& operator=(word&&) = delete;

	virtual std::string_view get() = 0;
};
