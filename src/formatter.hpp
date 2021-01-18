/*
This modules contains the actual formatter used to render output
Author: Dorian Lesbre
*/

#ifndef FORMATTER_HPP
#define FORMATTER_HPP

#include <string>
#include <vector>

#include "options.hpp"

std::string format(
	const std::string& csv,
	const settings& prgm_settings,
	const std::vector<unsigned int>& widths,
	unsigned int col_number
	);

#endif // FORMATTER_HPP