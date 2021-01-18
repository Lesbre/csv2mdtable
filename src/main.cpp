/* 
Small utility program to generate markdown table from csv files
Author: Dorian Lesbre
*/

#include "project.hpp"

#include <string>
#include <fstream>
#include <vector>

#include "options.hpp"
#include "io.hpp"
#include "parser.hpp"
#include "formatter.hpp"

int main(int argc, char ** argv) {
  // parse command line argumants                     
  int cmd_res = parse_cmd(argc, argv);
  if (cmd_res != 0) {
    if (cmd_res == -1)
      return 0;
    return 1; // cmd_res; // bad input error code
  }                                  

  // read csv input
  std::string csv = read(in_path);

  unsigned int align_len = align.size();
  unsigned int input_len = csv.length();
  if (input_len == 0) {
    printf_error("empty input (check path and permissions)\n");
    return 2; // invalid file error code   
  }

  if (auto_detect_sep) {
    if (!auto_detect_separator(csv, line_sep)) 
      return 3; // no suitable separator found
      // invalid csv error code
  }

  // column sizes for padding
  std::vector<unsigned int> widths;
  unsigned int col_number;
  if (use_padding) {
    widths = columns_width(csv, col_sep, line_sep);

    #ifdef DEBUG
      printf_debug("Column widths\n  ");
      for (unsigned int i = 0; i < widths.size(); ++i)
        std::cout << widths[i] << " ";
      std::cout << std::endl;
    #endif

    // minimum width is three dashes or 5 if align specified
    for (unsigned int i = 0; i < widths.size(); ++i) {
      if (i < align_len && align[i] != '_') {
        widths[i] = max(widths[i], 5);
      }
      else {
        widths[i] = max(widths[i], 3);
      }
    }

    col_number = widths.size();
  } else
    col_number = table_width(csv, col_sep, line_sep);

  while (align.size() < col_number) {
    align.push_back('_');
  }

  std::string output = format(csv, col_sep, line_sep, use_padding, ext_pipes, widths, align, col_number);

  if (write(out_path, output)) {
    printf_error("failed to write to '%s'. Check file path and permissions", out_path);
    return 4; // write failed
  }
  return 0;
}