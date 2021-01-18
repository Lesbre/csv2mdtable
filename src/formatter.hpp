/*
This modules contains the actual formatter used to render output
Author: Dorian Lesbre
*/

#ifndef FORMATTER_HPP
#define FORMATTER_HPP

#include <string>
#include <vector>

std::string format(
	const std::string& csv,
	const char& col_sep,
	const char& line_sep,
	const bool& use_padding,
	const bool& ext_pipes,
	const std::vector<unsigned int>& widths,
	const std::vector<char>& align,
	const unsigned int& col_number
	);

#endif // FORMATTER_HPP