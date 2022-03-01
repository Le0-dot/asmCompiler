#pragma once

#include <queue>
#include <string>
#include <map>
#include <functional>
#include <stdexcept>

#include "word/words.hpp"
#include "utils.hpp"

class scanner
{
    private:
	using iqueue = std::queue<char>;
	using oqueue = std::queue<word*>;

	iqueue& input_queue;
	oqueue& output_queue;

    public:
	scanner(iqueue& input_queue, oqueue& output_queue) :
	    input_queue{input_queue}, output_queue{output_queue} {}

	void run()
	{
	    std::map<char, std::function<std::string(std::string&)>> funcs {
		{'a', std::bind(&scanner::a_char, *this, std::placeholders::_1)},
		{'d', std::bind(&scanner::d_char, *this, std::placeholders::_1)},
		{'n', std::bind(&scanner::n_char, *this, std::placeholders::_1)},
		{'l', std::bind(&scanner::l_char, *this, std::placeholders::_1)},
		{'i', std::bind(&scanner::i_char, *this, std::placeholders::_1)},
		{'r', std::bind(&scanner::r_char, *this, std::placeholders::_1)},
		{'e', std::bind(&scanner::e_char, *this, std::placeholders::_1)},
		{'o', std::bind(&scanner::o_char, *this, std::placeholders::_1)},
		{'t', std::bind(&scanner::t_char, *this, std::placeholders::_1)},
		{'s', std::bind(&scanner::s_char, *this, std::placeholders::_1)},
		{'j', std::bind(&scanner::j_char, *this, std::placeholders::_1)},
		{'m', std::bind(&scanner::m_char, *this, std::placeholders::_1)},
		{'p', std::bind(&scanner::p_char, *this, std::placeholders::_1)},
		{'b', std::bind(&scanner::b_char, *this, std::placeholders::_1)},
		{'h', std::bind(&scanner::h_char, *this, std::placeholders::_1)}
	    };
	    std::string prev = "";
	    while(!input_queue.empty()) {
		char current = pop_queue(input_queue);
		if(current == ' ')
		    continue;
		prev = funcs[current](prev);
	    }
	}

    private:
	std::string a_char(std::string& prev)
	{
	    std::cerr << "scanner::a_char(\"" << prev << "\") [input_queue.front() = '" << input_queue.front() << "']" << std::endl;
	    if(prev == "" && (input_queue.front() != 'd' && input_queue.front() != 'n'))
		throw std::runtime_error(prev);
	    if(prev == "tr" && input_queue.front() != 'p')
		throw std::runtime_error(prev);
	    if(prev == "le" && input_queue.front() == ' ') {
		output_queue.push(new operation_word(operations::lea));
		return "";
	    }
	    if(prev == "h" && input_queue.front() != 'l')
		throw std::runtime_error(prev);
	    return prev + 'a';
	}

	std::string d_char(std::string& prev)
	{
	    std::cerr << "scanner::d_char(\"" << prev << "\") [input_queue.front() = '" << input_queue.front() << "']" << std::endl;
	    if(prev == "a" && input_queue.front() != 'd')
		throw std::runtime_error(prev);
	    if(prev == "ad" && input_queue.front() == ' ') {
		output_queue.push(new operation_word(operations::add));
		return "";
	    }
	    if(prev == "an" && input_queue.front() == ' ') {
		output_queue.push(new operation_word(operations::and_op));
		return "";
	    }
	    if(prev == "l" && input_queue.front() == ' ') {
		output_queue.push(new operation_word(operations::ld));
		return "";
	    }
	    if(prev == "l" && (input_queue.front() != 'i' && input_queue.front() != 'r'))
		throw std::runtime_error(prev);
	    return prev + 'd';
	}

	std::string n_char(std::string& prev)
	{
	    std::cerr << "scanner::n_char(\"" << prev << "\") [input_queue.front() = '" << input_queue.front() << "']" << std::endl;
	    if(prev == "" && input_queue.front() != 'o')
		throw std::runtime_error(prev);
	    if(prev == "a" && input_queue.front() != 'd')
		throw std::runtime_error(prev);
	    return prev + 'n';
	}

	std::string l_char(std::string& prev)
	{
	    std::cerr << "scanner::l_char(\"" << prev << "\") [input_queue.front() = '" << input_queue.front() << "']" << std::endl;
	    if(prev == "" && (input_queue.front() != 'd' &&
			      input_queue.front() != 'e'))
		throw std::runtime_error(prev);
	    if(prev == "ha" && input_queue.front() != 't')
		throw std::runtime_error(prev);
	    return prev + 'l';
	}

	std::string i_char(std::string& prev)
	{
	    std::cerr << "scanner::i_char(\"" << prev << "\") [input_queue.front() = '" << input_queue.front() << "']" << std::endl;
	    if(prev == "ld" && input_queue.front() == ' ') {
		output_queue.push(new operation_word(operations::ldi));
		return "";
	    }
	    if(prev == "st" && input_queue.front() == ' ') {
		output_queue.push(new operation_word(operations::sti));
		return "";
	    }
	    return prev + 'i';
	}

	std::string r_char(std::string& prev)
	{
	    std::cerr << "scanner::r_char(\"" << prev << "\") [input_queue.front() = '" << input_queue.front() << "']" << std::endl;
	    if(prev == "ld" && input_queue.front() == ' ') {
		output_queue.push(new operation_word(operations::ldr));
		return "";
	    }
	    if(prev == "st" && input_queue.front() == ' ') {
		output_queue.push(new operation_word(operations::str));
		return "";
	    }
	    if(prev == "js" && input_queue.front() == ' ') {
		output_queue.push(new operation_word(operations::jsr));
		return "";
	    }
	    if(prev == "b" && input_queue.front() == ' ') {
		output_queue.push(new operation_word(operations::br));
		return "";
	    }
	    if(prev == "t" && input_queue.front() != 'a')
		throw std::runtime_error(prev);
	    return prev + 'r';
	}

	std::string e_char(std::string& prev)
	{
	    std::cerr << "scanner::e_char(\"" << prev << "\") [input_queue.front() = '" << input_queue.front() << "']" << std::endl;
	    if(prev == "l" && input_queue.front() != 'a')
		throw std::runtime_error(prev);
	    return prev + 'e';
	}

	std::string o_char(std::string& prev)
	{
	    std::cerr << "scanner::o_char(\"" << prev << "\") [input_queue.front() = '" << input_queue.front() << "']" << std::endl;
	    if(prev == "n" && input_queue.front() != 't')
		throw std::runtime_error(prev);
	    return prev + 'o';
	}

	std::string t_char(std::string& prev)
	{
	    std::cerr << "scanner::t_char(\"" << prev << "\") [input_queue.front() = '" << input_queue.front() << "']" << std::endl;
	    if(prev == "no" && input_queue.front() == ' ') {
		output_queue.push(new operation_word(operations::not_op));
		return "";
	    }
	    if(prev == "s" && input_queue.front() == ' ') {
		output_queue.push(new operation_word(operations::st));
		return "";
	    }
	    if(prev == "hal" && input_queue.front() == ' ') {
		output_queue.push(new operation_word(operations::halt));
		return "";
	    }
	    if(prev == "s" && input_queue.front() != 'i' && 
		    input_queue.front() != 'r' && input_queue.front() != ' ')
		throw std::runtime_error(prev);
	    if(prev == "" && input_queue.front() != 'r')
		throw std::runtime_error(prev);
	    return prev + 't';
	}

	std::string s_char(std::string& prev)
	{
	    std::cerr << "scanner::s_char(\"" << prev << "\") [input_queue.front() = '" << input_queue.front() << "']" << std::endl;
	    if(prev == "" && input_queue.front() != 't')
		throw std::runtime_error(prev);
	    if(prev == "j" && input_queue.front() != 'r')
		throw std::runtime_error(prev);
	    return prev + 's';
	}

	std::string j_char(std::string& prev)
	{
	    std::cerr << "scanner::j_char(\"" << prev << "\") [input_queue.front() = '" << input_queue.front() << "']" << std::endl;
	    if(prev == "" && input_queue.front() != 'm' && input_queue.front() != 's')
		throw std::runtime_error(prev);
	    return prev + 'j';
	}

	std::string m_char(std::string& prev)
	{
	    std::cerr << "scanner::m_char(\"" << prev << "\") [input_queue.front() = '" << input_queue.front() << "']" << std::endl;
	    if(prev == "j" && input_queue.front() != 'p')
		throw std::runtime_error(prev);
	    return prev + 'm';
	}

	std::string p_char(std::string& prev)
	{
	    std::cerr << "scanner::p_char(\"" << prev << "\") [input_queue.front() = '" << input_queue.front() << "']" << std::endl;
	    if(prev == "jm" && input_queue.front() == ' ') {
		output_queue.push(new operation_word(operations::jmp));
		return "";
	    }
	    if(prev == "tra" && input_queue.front() == ' ') {
		output_queue.push(new operation_word(operations::trap));
		return "";
	    }
	    return prev + 'p';
	}

	std::string b_char(std::string& prev)
	{
	    std::cerr << "scanner::b_char(\"" << prev << "\") [input_queue.front() = '" << input_queue.front() << "']" << std::endl;
	    if(prev == "" && input_queue.front() != 'r')
		throw std::runtime_error(prev);
	    return prev + 'b';
	}

	std::string h_char(std::string& prev)
	{
	    std::cerr << "scanner::h_char(\"" << prev << "\") [input_queue.front() = '" << input_queue.front() << "']" << std::endl;
	    if(prev == "" && input_queue.front() != 'a')
		throw std::runtime_error(prev);
	    return prev + 'h';
	}
};
