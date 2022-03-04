#pragma once

#include <queue>
#include <stdexcept>
#include <cstring>
#include <cctype>
#include <cstdint>

#include "word/words.hpp"

template<typename T>
T pop_queue(std::queue<T>& queue)
{
    T val = queue.front();
    queue.pop();
    return val;
}

void error_handling(const std::runtime_error& e, std::queue<char>& input_queue)
{
    std::cout << "Syntax error: " << std::endl << e.what();
    char current;
    while(!input_queue.empty() && (current = pop_queue(input_queue)) != '\n')
	std::cout << current;
    std::cout << std::endl;
    for(int i = 0; i < strlen(e.what()) - 1; ++i)
	std::cout << ' ';
    std::cout << '^' << std::endl;
}

bool isnumber(const std::string& str)
{
    bool res = true;
    for(const auto& c: str)
	res = res && std::isdigit(c);
    return res;
}

std::ostream& operator<<(std::ostream& out, std::shared_ptr<word> w)
{
    switch(w->get()) {
	case words::operations:
	    out << otos(static_cast<operation_word*>(w.get())->get_op());
	    break;
	case words::registers:
	    out << rtos(static_cast<register_word*>(w.get())->get_reg());
	    break;
	case words::numbers:
	    out << static_cast<number_word<uint16_t>*>(w.get())->get_num();
	    break;
	case words::traps:
	    out << ttos(static_cast<trap_word*>(w.get())->get_trp());
	    break;
    }
    return out;
}

template<typename T>
struct typetostr { static constexpr auto v = ""; };

template<>
struct typetostr<uint16_t> { static constexpr auto v = "uint16_t"; };
