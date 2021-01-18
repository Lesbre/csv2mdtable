/*
This file contains functions for io from file or console
*/

#ifndef IO_HPP
#define IO_HPP

#include <string>
#include <fstream>

// std::string read_file(const char * path);
// std::string read_console();

//read from file or console
std::string read(const char * path);

// bool write_file(const char * path, const std::string& content);
// bool write_console(const std::string& content);

// false if success
bool write(const char * path, const std::string& content);

#endif // IO_HPP