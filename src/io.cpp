
#include "project.hpp"

#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include "io.hpp"

#ifdef POSIX
	// checks if tty or pipe
	#include <stdio.h>
	#include <unistd.h>
#endif

std::string read_file(const char * path) {
	std::ifstream input(path);
	std::stringstream sstr;

	while(input >> sstr.rdbuf());

	// std::cout << sstr.str() << "!" << std::endl;
	return sstr.str();
}

std::string read_console() {
	std::string total_input = "";
	std::string line_input;
	while (std::getline(std::cin, line_input)) {
		total_input.append(line_input);
		total_input.append("\n");
	}
	// std::cout << total_input << "!" << std::endl;
	return total_input;
}

std::string read(const char * path) {
	if (path != nullptr) {
		return read_file(path);
	}
	else {
		#ifdef POSIX
			if (isatty(fileno(stdin)) && isatty(fileno(stdout)))
				// only print prompt if interactive
				printf("%sEnter or paste the contents of the csv file\nEnd with Ctrl+D%s\n", Color_Yellow, Color_Reset);
		#else
			printf("%sEnter or paste the contents of the csv file\nEnd with Ctrl+D%s\n", Color_Yellow, Color_Reset);
		#endif
		return read_console();
	}
}

bool write_file(const char * path, const std::string& content) {
	std::ofstream out(path);
	if (!out.is_open())
		return true;
	out << content;
	// out.close();
	return false;
}
bool write_console(const std::string& content) {
	std::cout << content;
	return false;
}

bool write(const char * path, const std::string& content) {
	if (path == nullptr)
		return write_console(content);
	return write_file(path, content);
}