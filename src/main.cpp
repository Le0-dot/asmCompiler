#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include <cstdint>
#include <memory>

#include "scanner.hpp"
#include "parser.hpp"
#include "utils.hpp"
#include "logging_queue.hpp"

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

    logging_queue<char> input_queue("input_queue");
    for(char c; in; in >> std::noskipws >> c, input_queue.push(c));
    in.close();

    logging_queue<std::shared_ptr<word>> middle_queue("middle_queue");
    scanner<uint16_t> scan(input_queue, middle_queue);
    try {
	scan.run();
    } catch(std::runtime_error& e) {
	error_handling(e, input_queue);
	return 3;
    }

    logging_queue<uint16_t> output_queue("output_queue");
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
