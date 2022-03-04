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

	std::string name;
	iqueue& input_queue;
	oqueue& output_queue;

    public:
	scanner(iqueue& input_queue, oqueue& output_queue, std::string name = "scanner") :
	    name{name}, input_queue{input_queue}, output_queue{output_queue} {}

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
		{'h', std::bind(&scanner::h_char, *this, std::placeholders::_1)},
		{'g', std::bind(&scanner::g_char, *this, std::placeholders::_1)},
		{'c', std::bind(&scanner::c_char, *this, std::placeholders::_1)},
		{'u', std::bind(&scanner::u_char, *this, std::placeholders::_1)},
		{'_', std::bind(&scanner::underscore_char, *this, std::placeholders::_1)}
	    };
	    std::string prev = "";
	    while(!input_queue.empty()) {
		char current = pop_queue(input_queue);
		if(current == ' ')
		    continue;
		else if(current == '\n')
		    output_queue.push(std::make_shared<endline_word>(), "std::make_shared<endline_word>()");
		else if(std::isdigit(current))
		    prev = num_char(prev, current);
		else
		    prev = funcs[current](prev);
	    }
	}

    private:
	std::string a_char(const std::string& prev)
	{
	    std::cerr << name << ".a_char(\"" << prev << "\") [input_queue.front() = '" 
		<< (input_queue.front() == '\n' ? '\0' : input_queue.front()) << "']" << std::endl;
	    if(prev == "" && (input_queue.front() != 'd' && input_queue.front() != 'n'))
		throw std::runtime_error(prev + 'a');
	    if(prev == "tr" && input_queue.front() != 'p')
		throw std::runtime_error(prev + 'a');
	    if(prev == "le" && std::isspace(input_queue.front())) {
		output_queue.push(std::make_shared<operation_word>(operations::lea),
			"std::make_shared<operation_word>(operations::" + otos(operations::lea) + ")");
		return "";
	    }
	    if(prev == "h" && input_queue.front() != 'l')
		throw std::runtime_error(prev + 'a');
	    return prev + 'a';
	}

	std::string d_char(const std::string& prev)
	{
	    std::cerr << name << ".d_char(\"" << prev << "\") [input_queue.front() = '"
		<< (input_queue.front() == '\n' ? '\0' : input_queue.front()) << "']" << std::endl;
	    if(prev == "a" && input_queue.front() != 'd')
		throw std::runtime_error(prev + 'd');
	    if(prev == "ad" && std::isspace(input_queue.front())) {
		output_queue.push(std::make_shared<operation_word>(operations::add),
			"std::make_shared<operation_word>(operations::" + otos(operations::add) + ")");
		return "";
	    }
	    if(prev == "an" && std::isspace(input_queue.front())) {
		output_queue.push(std::make_shared<operation_word>(operations::and_op),
			"std::make_shared<operation_word>(operations::" + otos(operations::and_op) + ")");
		return "";
	    }
	    if(prev == "l" && std::isspace(input_queue.front())) {
		output_queue.push(std::make_shared<operation_word>(operations::ld),
			"std::make_shared<operation_word>(operations::" + otos(operations::ld) + ")");
		return "";
	    }
	    if(prev == "l" && (input_queue.front() != 'i' && input_queue.front() != 'r'))
		throw std::runtime_error(prev + 'd');
	    return prev + 'd';
	}

	std::string n_char(const std::string& prev)
	{
	    std::cerr << name << ".n_char(\"" << prev << "\") [input_queue.front() = '" 
		<< (input_queue.front() == '\n' ? '\0' : input_queue.front()) << "']" << std::endl;
	    if(prev == "" && input_queue.front() != 'o')
		throw std::runtime_error(prev + 'n');
	    if(prev == "a" && input_queue.front() != 'd')
		throw std::runtime_error(prev + 'n');
	    if(prev == "trp_i" && std::isspace(input_queue.front())) {
		output_queue.push(std::make_shared<trap_word>(traps::trp_in),
			"std::make_shared<trap_word>(traps::" + ttos(traps::trp_in) + ")");
		return "";
	    }
	    if(prev == "trp_i" && input_queue.front() != '_')
		throw std::runtime_error(prev + 'n');
	    return prev + 'n';
	}

	std::string l_char(const std::string& prev)
	{
	    std::cerr << name << ".l_char(\"" << prev << "\") [input_queue.front() = '" 
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
	    std::cerr << name << ".i_char(\"" << prev << "\") [input_queue.front() = '" 
		<< (input_queue.front() == '\n' ? '\0' : input_queue.front()) << "']" << std::endl;
	    if(prev == "ld" && std::isspace(input_queue.front())) {
		output_queue.push(std::make_shared<operation_word>(operations::ldi),
			"std::make_shared<operation_word>(operations::" + otos(operations::ldi) + ")");
		return "";
	    }
	    if(prev == "st" && std::isspace(input_queue.front())) {
		output_queue.push(std::make_shared<operation_word>(operations::sti),
			"std::make_shared<operation_word>(operations::" + otos(operations::sti) + ")");
		return "";
	    }
	    if(prev == "trp_" && input_queue.front() != 'n')
		throw std::runtime_error(prev + 'i');
	    return prev + 'i';
	}

	std::string r_char(const std::string& prev)
	{
	    std::cerr << name << ".r_char(\"" << prev << "\") [input_queue.front() = '" 
		<< (input_queue.front() == '\n' ? '\0' : input_queue.front()) << "']" << std::endl;
	    if(prev == "ld" && std::isspace(input_queue.front())) {
		output_queue.push(std::make_shared<operation_word>(operations::ldr),
			"std::make_shared<operation_word>(operations::" + otos(operations::ldr) + ")");
		return "";
	    }
	    if(prev == "st" && std::isspace(input_queue.front())) {
		output_queue.push(std::make_shared<operation_word>(operations::str),
			"std::make_shared<operation_word>(operations::" + otos(operations::str) + ")");
		return "";
	    }
	    if(prev == "js" && std::isspace(input_queue.front())) {
		output_queue.push(std::make_shared<operation_word>(operations::jsr),
			"std::make_shared<operation_word>(operations::" + otos(operations::jsr) + ")");
		return "";
	    }
	    if(prev == "jsr" && std::isspace(input_queue.front())) {
		output_queue.push(std::make_shared<operation_word>(operations::jsrr),
			"std::make_shared<operation_word>(operations::" + otos(operations::jsrr) + ")");
		return "";
	    }
	    if(prev == "b" && std::isspace(input_queue.front())) {
		output_queue.push(std::make_shared<operation_word>(operations::br),
			"std::make_shared<operation_word>(operations::" + otos(operations::br) + ")");
		return "";
	    }
	    if(prev == "t" && input_queue.front() != 'a' && input_queue.front() != 'p')
		throw std::runtime_error(prev + 'r');
	    return prev + 'r';
	}

	std::string e_char(const std::string& prev)
	{
	    std::cerr << name << ".e_char(\"" << prev << "\") [input_queue.front() = '" 
		<< (input_queue.front() == '\n' ? '\0' : input_queue.front()) << "']" << std::endl;
	    if(prev == "l" && input_queue.front() != 'a')
		throw std::runtime_error(prev + 'e');
	    if(prev == "trp_g" && input_queue.front() != 't')
		throw std::runtime_error(prev + 'e');
	    return prev + 'e';
	}

	std::string o_char(const std::string& prev)
	{
	    std::cerr << name << ".o_char(\"" << prev << "\") [input_queue.front() = '" 
		<< (input_queue.front() == '\n' ? '\0' : input_queue.front()) << "']" << std::endl;
	    if(prev == "n" && input_queue.front() != 't')
		throw std::runtime_error(prev + 'o');
	    if(prev == "trp_" && input_queue.front() != 'u')
		throw std::runtime_error(prev + 'o');
	    return prev + 'o';
	}

	std::string t_char(const std::string& prev)
	{
	    std::cerr << name << ".t_char(\"" << prev << "\") [input_queue.front() = '" 
		<< (input_queue.front() == '\n' ? '\0' : input_queue.front()) << "']" << std::endl;
	    if(prev == "no" && std::isspace(input_queue.front())) {
		output_queue.push(std::make_shared<operation_word>(operations::not_op),
			"std::make_shared<operation_word>(operations::" + otos(operations::not_op) + ")");
		return "";
	    }
	    if(prev == "s" && std::isspace(input_queue.front())) {
		output_queue.push(std::make_shared<operation_word>(operations::st),
			"std::make_shared<operation_word>(operations::" + otos(operations::st) + ")");
		return "";
	    }
	    if(prev == "hal" && std::isspace(input_queue.front())) {
		output_queue.push(std::make_shared<operation_word>(operations::halt),
			"std::make_shared<operation_word>(operations::" + otos(operations::halt) + ")");
		return "";
	    }
	    if(prev == "trp_ou" && std::isspace(input_queue.front())) {
		output_queue.push(std::make_shared<trap_word>(traps::trp_out),
			"std::make_shared<trap_word>(traps::" + ttos(traps::trp_out) + ")");
		return "";
	    }
	    if((prev == "trp_ou" || prev == "trp_pu") && input_queue.front() != '_')
		throw std::runtime_error(prev + 't');
	    if(prev == "s" && input_queue.front() != 'i' && 
		    input_queue.front() != 'r' && input_queue.front() != ' ')
		throw std::runtime_error(prev + 't');
	    if(prev == "" && input_queue.front() != 'r')
		throw std::runtime_error(prev + 't');
	    if(prev == "trp_ge" && input_queue.front() != '_')
		throw std::runtime_error(prev + 't');
	    return prev + 't';
	}

	std::string s_char(const std::string& prev)
	{
	    std::cerr << name << ".s_char(\"" << prev << "\") [input_queue.front() = '" 
		<< (input_queue.front() == '\n' ? '\0' : input_queue.front()) << "']" << std::endl;
	    if(prev == "" && input_queue.front() != 't')
		throw std::runtime_error(prev + 's');
	    if(prev == "j" && input_queue.front() != 'r')
		throw std::runtime_error(prev + 's');
	    if(prev == "trp_put_" && std::isspace(input_queue.front())) {
		output_queue.push(std::make_shared<trap_word>(traps::trp_put_s),
			"std::make_shared<trap_word>(traps::" + ttos(traps::trp_put_s) + ")");
		return "";
	    }
	    return prev + 's';
	}

	std::string j_char(const std::string& prev)
	{
	    std::cerr << name << ".j_char(\"" << prev << "\") [input_queue.front() = '" 
		<< (input_queue.front() == '\n' ? '\0' : input_queue.front()) << "']" << std::endl;
	    if(prev == "" && input_queue.front() != 'm' && input_queue.front() != 's')
		throw std::runtime_error(prev + 'j');
	    return prev + 'j';
	}

	std::string m_char(const std::string& prev)
	{
	    std::cerr << name << ".m_char(\"" << prev << "\") [input_queue.front() = '" 
		<< (input_queue.front() == '\n' ? '\0' : input_queue.front()) << "']" << std::endl;
	    if(prev == "j" && input_queue.front() != 'p')
		throw std::runtime_error(prev + 'm');
	    return prev + 'm';
	}

	std::string p_char(const std::string& prev)
	{
	    std::cerr << name << ".p_char(\"" << prev << "\") [input_queue.front() = '" 
		<< (input_queue.front() == '\n' ? '\0' : input_queue.front()) << "']" << std::endl;
	    if(prev == "jm" && std::isspace(input_queue.front())) {
		output_queue.push(std::make_shared<operation_word>(operations::jmp),
			"std::make_shared<operation_word>(operations::" + otos(operations::jmp) + ")");
		return "";
	    }
	    if(prev == "tra" && std::isspace(input_queue.front())) {
		output_queue.push(std::make_shared<operation_word>(operations::trap),
			"std::make_shared<operation_word>(operations::" + otos(operations::trap) + ")");
		return "";
	    }
	    if(prev == "tr" && input_queue.front() != '_')
		throw std::runtime_error(prev + 'p');
	    if(prev == "trp_" && input_queue.front() != 'u')
		throw std::runtime_error(prev + 'p');
	    return prev + 'p';
	}

	std::string b_char(const std::string& prev)
	{
	    std::cerr << name << ".b_char(\"" << prev << "\") [input_queue.front() = '" 
		<< (input_queue.front() == '\n' ? '\0' : input_queue.front()) << "']" << std::endl;
	    if(prev == "" && input_queue.front() != 'r')
		throw std::runtime_error(prev + 'b');
	    return prev + 'b';
	}

	std::string h_char(const std::string& prev)
	{
	    std::cerr << name << ".h_char(\"" << prev << "\") [input_queue.front() = '" 
		<< (input_queue.front() == '\n' ? '\0' : input_queue.front()) << "']" << std::endl;
	    if(prev == "" && input_queue.front() != 'a')
		throw std::runtime_error(prev + 'h');
	    return prev + 'h';
	}

	std::string g_char(const std::string& prev)
	{
	    std::cerr << name << ".g_char(\"" << prev << "\") [input_queue.front() = '" 
		<< (input_queue.front() == '\n' ? '\0' : input_queue.front()) << "']" << std::endl;
	    if(prev == "trp_" && input_queue.front() != 'e')
		throw std::runtime_error(prev + 'g');
	    return prev + 'g';
	}

	std::string c_char(const std::string& prev)
	{
	    std::cerr << name << ".c_char(\"" << prev << "\") [input_queue.front() = '" 
		<< (input_queue.front() == '\n' ? '\0' : input_queue.front()) << "']" << std::endl;
	    if(prev == "trp_get_" && std::isspace(input_queue.front())) {
		output_queue.push(std::make_shared<trap_word>(traps::trp_get_c), 
			"std::make_shared<trap_word>(traps::" + ttos(traps::trp_get_c) + ")");
		return "";

	    }
	    return prev + 'c';
	}

	std::string u_char(const std::string& prev)
	{
	    std::cerr << name << ".u_char(\"" << prev << "\") [input_queue.front() = '" 
		<< (input_queue.front() == '\n' ? '\0' : input_queue.front()) << "']" << std::endl;
	    if((prev == "trp_o" || prev == "trp_p") && input_queue.front() != 't')
		throw std::runtime_error(prev + 'u');
	    if((prev == "trp_in_" || prev == "trp_out_") && input_queue.front() != '1')
		throw std::runtime_error(prev + 'u');
	    return prev + 'u';
	}

	std::string num_char(const std::string& prev, char current)
	{
	    std::cerr << name << ".num_char(\"" << prev << "\", '" << current 
		<< "') [input_queue.front() = '" << (input_queue.front() == '\n' ? '\0' : input_queue.front()) << "']" << std::endl;
	    if(prev == "r" && std::isspace(input_queue.front()) && current != '8' && current != '9') {
		output_queue.push(std::make_shared<register_word>(ntor(current)),
			std::string("std::make_shared<register_word>(registers::r") + current + ")");
		return "";
	    }
	    if((prev == "" || isnumber(prev)) && std::isspace(input_queue.front())) {
		output_queue.push(std::make_shared<number_word<num>>(std::stoul(prev + current)),
			std::string("std::make_shared<number_word<") + typetostr<num>::v + ">>(" + prev + current + ")");
		return "";
	    }
	    if((prev == "" || isnumber(prev)) && !std::isdigit(input_queue.front()) && !std::isspace(input_queue.front()))
		throw std::runtime_error(prev + current);
	    if((prev == "trp_in_u" || prev == "trp_out_u") && (current != '1' || input_queue.front() != '6'))
		throw std::runtime_error(prev + current);
	    if(prev == "trp_in_u1" && current == '6' && std::isspace(input_queue.front())) {
		output_queue.push(std::make_shared<trap_word>(traps::trp_in_u16),
			std::string("std::make_shared<trap_word>(traps::") + ttos(traps::trp_in_u16) + ")");
		return "";
	    }
	    if(prev == "trp_out_u1" && current == '6' && std::isspace(input_queue.front())) {
		output_queue.push(std::make_shared<trap_word>(traps::trp_out_u16),
			std::string("std::make_shared<trap_word>(traps::") + ttos(traps::trp_out_u16) + ")");
		return "";
	    }
	    return prev + current;
	}

	std::string underscore_char(const std::string& prev)
	{
	    std::cerr << name << ".underscore_char(\"" << prev << "\") [input_queue.front() = '" 
		<< (input_queue.front() == '\n' ? '\0' : input_queue.front()) << "']" << std::endl;
	    if(prev == "trp" && input_queue.front() != 'g' &&
				input_queue.front() != 'o' &&
				input_queue.front() != 'p' &&
				input_queue.front() != 'i')
		throw std::runtime_error(prev + '_');
	    if(prev == "trp_get" && input_queue.front() != 'c')
		throw std::runtime_error(prev + '_');
	    if(prev == "trp_in" && input_queue.front() != 'u')
		throw std::runtime_error(prev + '_');
	    if(prev == "trp_out" && input_queue.front() != 'u')
		throw std::runtime_error(prev + '_');
	    if(prev == "trp_put" && input_queue.front() != 's')
		throw std::runtime_error(prev + '_');
	    return prev + '_';
	}
};
