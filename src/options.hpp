/*
This file handle the command line parsing and set the program options
Options are packed in a settings class
Author: Dorian Lesbre
*/

#ifndef OPTIONS_HPP
#define OPTIONS_HPP

#include <vector>

// Options as globals
extern bool use_padding;
extern bool ext_pipes;
extern bool auto_detect_sep;
extern char col_sep;
extern char line_sep;
extern char * in_path;
extern char * out_path;
extern std::vector<char> align;

// CMD parser
// set the options
// returns 0  if continue program
//         -1 if show help/version (normal exit)
//         n  if error 
int parse_cmd(int argc, char ** argv);

#endif // OPTIONS_HPP