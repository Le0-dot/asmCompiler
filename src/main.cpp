#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <stdexcept>
#include <cstdint>

#include "scanner.hpp"
#include "parser.hpp"

int main(int argc, char** argv)
{
    if(argc < 2) {
	std::cout << "Input file should be passed as argument" << std::endl;
	return 1;
    }
    
    std::ifstream in(argv[1]);
    if(!in.is_open()) {
	std::cout << "Unable to open file: " << argv[1] << std::endl;
	return 2;
    }

    std::queue<std::string> input_queue;
    for(std::string in_str; std::getline(in, in_str); input_queue.push(in_str));
    in.close();

    std::queue</* ??? */std::string> middle_queue;
    scanner scan(input_queue, middle_queue);
    try {
	scan.run();
    } catch(std::runtime_error& e) {
	std::cout << e.what() << std::endl;
	return 3;
    }

    std::queue<uint16_t> output_queue;
    parser<uint16_t> pars(middle_queue, output_queue);
    try {
	pars.run();
    } catch(std::runtime_error& e) {
	std::cout << e.what() << std::endl;
	return 4;
    }

    std::ofstream out((argc == 3 ? argv[2] : "program.obj"), std::ios_base::binary);
    for(uint16_t instruction; !output_queue.empty(); instruction = output_queue.front(), output_queue.pop())
	out.write(reinterpret_cast<char*>(&instruction), sizeof(uint16_t));
    out.close();

    return 0;
}
