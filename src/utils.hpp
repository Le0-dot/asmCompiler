#pragma once

#include <queue>
#include <stdexcept>
#include <cstring>

template<typename T>
T pop_queue(std::queue<T>& queue)
{
    T val = queue.front();
    queue.pop();
    return val;
}

void error_handling(std::runtime_error& e, std::queue<char>& input_queue)
{
    std::cout << "Syntax error: " << std::endl << e.what();
    char current;
    while((current = pop_queue(input_queue)) != '\n')
	std::cout << current;
    std::cout << std::endl;
    for(int i = 0; i < strlen(e.what()) - 1; ++i)
	std::cout << ' ';
    std::cout << '^' << std::endl;
}

void push_string_to_queue(std::string str, std::queue<char>& queue)
{
    for(const auto& c: str)
	queue.push(c);
}
