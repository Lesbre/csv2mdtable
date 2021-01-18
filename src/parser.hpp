/*
This module contains functions for parsing and analysing the csv file
Author: Dorian Lesbre
*/

#ifndef PARSER_HPP
#define PARSER_HPP

#include <string>
#include <vector>

#define max(a,b) ((a) > (b) ? (a) : (b))

// attempt to auto detect separator
// returns 0 on failure
char auto_detect_separator(const std::string& file, const char line_sep);

// column width in number of characters
std::vector<unsigned int> columns_width(const std::string& file, const char col_sep, const char line_sep);

unsigned int table_width(const std::string& file, const char col_sep, const char line_sep);


#endif // PARSER_HPP