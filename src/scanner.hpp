#pragma once

#include <string>
#include <map>
#include <functional>
#include <stdexcept>
#include <memory>
#include <cctype>

#include "word/words.hpp"
#include "utils.hpp"
#include "logging_queue.hpp"

template<typename num>
class scanner
{
    private:
	using iqueue = logging_queue<char>;
	using oqueue = logging_queue<std::shared_ptr<word>>;

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
		else if(current == '\n') {
		    output_queue.push(std::make_shared<endline_word>(), "std::make_shared<endline_word>()");
		    std::cerr << "output_queue.push(std::make_shared<endline_word>())" << std::endl;
		} else if(std::isdigit(current))
		    prev = num_char(prev, current);
		else
		    prev = funcs[current](prev);
	    }
	}

    private:
	std::string a_char(const std::string& prev)
	{
	    std::cerr << "scanner::a_char(\"" << prev << "\") [input_queue.front() = '" 
		<< (input_queue.front() == '\n' ? '\0' : input_queue.front()) << "']" << std::endl;
	    if(prev == "" && (input_queue.front() != 'd' && input_queue.front() != 'n'))
		throw std::runtime_error(prev + 'a');
	    if(prev == "tr" && input_queue.front() != 'p')
		throw std::runtime_error(prev + 'a');
	    if(prev == "le" && std::isspace(input_queue.front())) {
		output_queue.push(std::make_shared<operation_word>(operations::lea));
		std::cerr << "output_queue.push(std::make_shared<operation_word>(operations::" << output_queue.back() << "))" << std::endl;
		return "";
	    }
	    if(prev == "h" && input_queue.front() != 'l')
		throw std::runtime_error(prev + 'a');
	    return prev + 'a';
	}

	std::string d_char(const std::string& prev)
	{
	    std::cerr << "scanner::d_char(\"" << prev << "\") [input_queue.front() = '"
		<< (input_queue.front() == '\n' ? '\0' : input_queue.front()) << "']" << std::endl;
	    if(prev == "a" && input_queue.front() != 'd')
		throw std::runtime_error(prev + 'd');
	    if(prev == "ad" && std::isspace(input_queue.front())) {
		output_queue.push(std::make_shared<operation_word>(operations::add));
		std::cerr << "output_queue.push(std::make_shared<operation_word>(operations::" << output_queue.back() << "))" << std::endl;
		return "";
	    }
	    if(prev == "an" && std::isspace(input_queue.front())) {
		output_queue.push(std::make_shared<operation_word>(operations::and_op));
		std::cerr << "output_queue.push(std::make_shared<operation_word>(operations::" << output_queue.back() << "))" << std::endl;
		return "";
	    }
	    if(prev == "l" && std::isspace(input_queue.front())) {
		output_queue.push(std::make_shared<operation_word>(operations::ld));
		std::cerr << "output_queue.push(std::make_shared<operation_word>(operations::" << output_queue.back() << "))" << std::endl;
		return "";
	    }
	    if(prev == "l" && (input_queue.front() != 'i' && input_queue.front() != 'r'))
		throw std::runtime_error(prev + 'd');
	    return prev + 'd';
	}

	std::string n_char(const std::string& prev)
	{
	    std::cerr << "scanner::n_char(\"" << prev << "\") [input_queue.front() = '" 
		<< (input_queue.front() == '\n' ? '\0' : input_queue.front()) << "']" << std::endl;
	    if(prev == "" && input_queue.front() != 'o')
		throw std::runtime_error(prev + 'n');
	    if(prev == "a" && input_queue.front() != 'd')
		throw std::runtime_error(prev + 'n');
	    return prev + 'n';
	}

	std::string l_char(const std::string& prev)
	{
	    std::cerr << "scanner::l_char(\"" << prev << "\") [input_queue.front() = '" 
		<< (input_queue.front() == '\n' ? '\0' : input_queue.front()) << "']" << std::endl;
	    if(prev == "" && (input_queue.front() != 'd' &&
			      input_queue.front() != 'e'))
		throw std::runtime_error(prev + 'l');
	    if(prev == "ha" && input_queue.front() != 't')
		throw std::runtime_error(prev + 'l');
	    return prev + 'l';
	}

	std::string i_char(const std::string& prev)
	{
	    std::cerr << "scanner::i_char(\"" << prev << "\") [input_queue.front() = '" 
		<< (input_queue.front() == '\n' ? '\0' : input_queue.front()) << "']" << std::endl;
	    if(prev == "ld" && std::isspace(input_queue.front())) {
		output_queue.push(std::make_shared<operation_word>(operations::ldi));
		std::cerr << "output_queue.push(std::make_shared<operation_word>(operations::" << output_queue.back() << "))" << std::endl;
		return "";
	    }
	    if(prev == "st" && std::isspace(input_queue.front())) {
		output_queue.push(std::make_shared<operation_word>(operations::sti));
		std::cerr << "output_queue.push(std::make_shared<operation_word>(operations::" << output_queue.back() << "))" << std::endl;
		return "";
	    }
	    return prev + 'i';
	}

	std::string r_char(const std::string& prev)
	{
	    std::cerr << "scanner::r_char(\"" << prev << "\") [input_queue.front() = '" 
		<< (input_queue.front() == '\n' ? '\0' : input_queue.front()) << "']" << std::endl;
	    if(prev == "ld" && std::isspace(input_queue.front())) {
		output_queue.push(std::make_shared<operation_word>(operations::ldr));
		std::cerr << "output_queue.push(std::make_shared<operation_word>(operations::" << output_queue.back() << "))" << std::endl;
		return "";
	    }
	    if(prev == "st" && std::isspace(input_queue.front())) {
		output_queue.push(std::make_shared<operation_word>(operations::str));
		std::cerr << "output_queue.push(std::make_shared<operation_word>(operations::" << output_queue.back() << "))" << std::endl;
		return "";
	    }
	    if(prev == "js" && std::isspace(input_queue.front())) {
		output_queue.push(std::make_shared<operation_word>(operations::jsr));
		std::cerr << "output_queue.push(std::make_shared<operation_word>(operations::" << output_queue.back() << "))" << std::endl;
		return "";
	    }
	    if(prev == "jsr" && std::isspace(input_queue.front())) {
		output_queue.push(std::make_shared<operation_word>(operations::jsrr));
		std::cerr << "output_queue.push(std::make_shared<operation_word>(operations::" << output_queue.back() << "))" << std::endl;
		return "";
	    }
	    if(prev == "b" && std::isspace(input_queue.front())) {
		output_queue.push(std::make_shared<operation_word>(operations::br));
		std::cerr << "output_queue.push(std::make_shared<operation_word>(operations::" << output_queue.back() << "))" << std::endl;
		return "";
	    }
	    if(prev == "t" && input_queue.front() != 'a')
		throw std::runtime_error(prev + 'r');
	    return prev + 'r';
	}

	std::string e_char(const std::string& prev)
	{
	    std::cerr << "scanner::e_char(\"" << prev << "\") [input_queue.front() = '" 
		<< (input_queue.front() == '\n' ? '\0' : input_queue.front()) << "']" << std::endl;
	    if(prev == "l" && input_queue.front() != 'a')
		throw std::runtime_error(prev + 'e');
	    return prev + 'e';
	}

	std::string o_char(const std::string& prev)
	{
	    std::cerr << "scanner::o_char(\"" << prev << "\") [input_queue.front() = '" 
		<< (input_queue.front() == '\n' ? '\0' : input_queue.front()) << "']" << std::endl;
	    if(prev == "n" && input_queue.front() != 't')
		throw std::runtime_error(prev + 'o');
	    return prev + 'o';
	}

	std::string t_char(const std::string& prev)
	{
	    std::cerr << "scanner::t_char(\"" << prev << "\") [input_queue.front() = '" 
		<< (input_queue.front() == '\n' ? '\0' : input_queue.front()) << "']" << std::endl;
	    if(prev == "no" && std::isspace(input_queue.front())) {
		output_queue.push(std::make_shared<operation_word>(operations::not_op));
		std::cerr << "output_queue.push(std::make_shared<operation_word>(operations::" << output_queue.back() << "))" << std::endl;
		return "";
	    }
	    if(prev == "s" && std::isspace(input_queue.front())) {
		output_queue.push(std::make_shared<operation_word>(operations::st));
		std::cerr << "output_queue.push(std::make_shared<operation_word>(operations::" << output_queue.back() << "))" << std::endl;
		return "";
	    }
	    if(prev == "hal" && std::isspace(input_queue.front())) {
		output_queue.push(std::make_shared<operation_word>(operations::halt));
		std::cerr << "output_queue.push(std::make_shared<operation_word>(operations::" << output_queue.back() << "))" << std::endl;
		return "";
	    }
	    if(prev == "s" && input_queue.front() != 'i' && 
		    input_queue.front() != 'r' && input_queue.front() != ' ')
		throw std::runtime_error(prev + 't');
	    if(prev == "" && input_queue.front() != 'r')
		throw std::runtime_error(prev + 't');
	    return prev + 't';
	}

	std::string s_char(const std::string& prev)
	{
	    std::cerr << "scanner::s_char(\"" << prev << "\") [input_queue.front() = '" 
		<< (input_queue.front() == '\n' ? '\0' : input_queue.front()) << "']" << std::endl;
	    if(prev == "" && input_queue.front() != 't')
		throw std::runtime_error(prev + 's');
	    if(prev == "j" && input_queue.front() != 'r')
		throw std::runtime_error(prev + 's');
	    return prev + 's';
	}

	std::string j_char(const std::string& prev)
	{
	    std::cerr << "scanner::j_char(\"" << prev << "\") [input_queue.front() = '" 
		<< (input_queue.front() == '\n' ? '\0' : input_queue.front()) << "']" << std::endl;
	    if(prev == "" && input_queue.front() != 'm' && input_queue.front() != 's')
		throw std::runtime_error(prev + 'j');
	    return prev + 'j';
	}

	std::string m_char(const std::string& prev)
	{
	    std::cerr << "scanner::m_char(\"" << prev << "\") [input_queue.front() = '" 
		<< (input_queue.front() == '\n' ? '\0' : input_queue.front()) << "']" << std::endl;
	    if(prev == "j" && input_queue.front() != 'p')
		throw std::runtime_error(prev + 'm');
	    return prev + 'm';
	}

	std::string p_char(const std::string& prev)
	{
	    std::cerr << "scanner::p_char(\"" << prev << "\") [input_queue.front() = '" 
		<< (input_queue.front() == '\n' ? '\0' : input_queue.front()) << "']" << std::endl;
	    if(prev == "jm" && std::isspace(input_queue.front())) {
		output_queue.push(std::make_shared<operation_word>(operations::jmp));
		std::cerr << "output_queue.push(std::make_shared<operation_word>(operations::" << output_queue.back() << "))" << std::endl;
		return "";
	    }
	    if(prev == "tra" && std::isspace(input_queue.front())) {
		output_queue.push(std::make_shared<operation_word>(operations::trap));
		std::cerr << "output_queue.push(std::make_shared<operation_word>(operations::" << output_queue.back() << "))" << std::endl;
		return "";
	    }
	    return prev + 'p';
	}

	std::string b_char(const std::string& prev)
	{
	    std::cerr << "scanner::b_char(\"" << prev << "\") [input_queue.front() = '" 
		<< (input_queue.front() == '\n' ? '\0' : input_queue.front()) << "']" << std::endl;
	    if(prev == "" && input_queue.front() != 'r')
		throw std::runtime_error(prev + 'b');
	    return prev + 'b';
	}

	std::string h_char(const std::string& prev)
	{
	    std::cerr << "scanner::h_char(\"" << prev << "\") [input_queue.front() = '" 
		<< (input_queue.front() == '\n' ? '\0' : input_queue.front()) << "']" << std::endl;
	    if(prev == "" && input_queue.front() != 'a')
		throw std::runtime_error(prev + 'h');
	    return prev + 'h';
	}

	std::string num_char(const std::string& prev, char current)
	{
	    std::cerr << "scanner::num_char(\"" << prev << "\", '" << current 
		<< "') [input_queue.front() = '" << (input_queue.front() == '\n' ? '\0' : input_queue.front()) << "']" << std::endl;
	    if(prev == "r" && std::isspace(input_queue.front()) && current != '8' && current != '9') {
		output_queue.push(std::make_shared<register_word>(ntor(current)));
		std::cerr << "output_queue.push(std::make_shared<register_word>(registers::" << output_queue.back() << "))" << std::endl;
		return "";
	    }
	    if((prev == "" || isnumber(prev)) && std::isspace(input_queue.front())) {
		output_queue.push(std::make_shared<number_word<num>>(std::stoul(prev + current)));
		std::cerr << "output_queue.push(std::make_shared<number_word<" << ttos<num>::v << ">>(" << output_queue.back() << "))" << std::endl;
		return "";
	    }
	    if((prev == "" || isnumber(prev)) && !std::isdigit(input_queue.front()) && !std::isspace(input_queue.front()))
		throw std::runtime_error(prev + current);
	    return prev + current;
	}
};
