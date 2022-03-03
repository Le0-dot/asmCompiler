#pragma once

#include <iostream>
#include <queue>
#include <string>

template<typename T>
class logging_queue : public std::queue<T>
{
    private:
	const std::string name;

    public:
	logging_queue(const std::string name) :
	    name{name} {}

	void push(const T& val, const std::string& log)
	{
	    std::cerr << name << ".push(" << log << ")" << std::endl;
	    this->std::queue<T>::push(val);
	}

	void push(T&& val, const std::string& log)
	{
	    std::cerr << name << ".push(" << log << ")" << std::endl;
	    this->std::queue<T>::push(val);
	}

	void pop()
	{
	    std::cerr << name << ".pop()" << std::endl;
	    this->std::queue<T>::pop();
	}
};
