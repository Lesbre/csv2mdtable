/*
This file handle the command line parsing and set the program options
Options are packed in a settings class
Author: Dorian Lesbre
*/

#ifndef OPTIONS_HPP
#define OPTIONS_HPP

#include <vector>

struct settings {
	bool use_padding;
	bool ext_pipes;
	bool auto_detect_sep;
	char col_sep;
	char line_sep;
	char * in_path;
	char * out_path;
	std::vector<char> align;
};


// CMD parser
// set the options
// returns 0  if continue program
//         -1 if show help/version (normal exit)
//         n  if error
int parse_cmd(int argc, char ** argv, settings& prgm_settings);

#endif // OPTIONS_HPP