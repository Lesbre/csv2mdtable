// see header for doc

#include "project.hpp"

#include "formatter.hpp"

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
		) {
	std::string output = "";
	unsigned int input_len = csv.length();
	unsigned int col_id = 0;
	unsigned int cell_start = 0;
	bool first_line = true;
	for (unsigned int i = 0; i < input_len; ++i) {

		if (csv[i] == col_sep || csv[i] == line_sep) {
			// printf_debug("%d %d %d ", i, cell_start, col_id);
			std::string cell = csv.substr(cell_start, i - cell_start);
			unsigned int cell_len = i - cell_start;

			if (use_padding) { // pad cell with spaces
				unsigned int missing = widths[col_id] - cell_len;
				switch (align[col_id])
				{
				case 'r':
					cell.insert(0, missing, ' ');
					break;
				case 'c':
					cell.append(missing / 2, ' ');
					cell.insert(0, missing - (missing / 2), ' ');
					break;
				default:
					cell.append(missing, ' ');
					break;
				}
			}
			// inserts cell in output
			if (ext_pipes && col_id == 0) // leading pipe
				output.append("|");
			output.append(cell);
			if (col_id != col_number - 1 || ext_pipes)
				output.append("|");

			if (csv[i] == col_sep)
				++col_id;
			else { // end line
				// pad missing cells
				for (++col_id; col_id < col_number; ++col_id) {
					output.append(widths[col_id], ' ');
					if (col_id != col_number - 1 || ext_pipes)
						output.append("|");
				}
				// insert new line
				output.append("\n");
				// insert dash line on second line
				if (first_line) {

					if (ext_pipes)
						output.append("|");
					for (col_id = 0; col_id < col_number; ++col_id) {
						if (use_padding) {
							switch (align[col_id])
							{
							case 'l':
								output.append(":");
								output.append(widths[col_id] - 1, '-');
								break;
							case 'r':
								output.append(widths[col_id] - 1, '-');
								output.append(":");
								break;
							case 'c':
								output.append(":");
								output.append(widths[col_id] - 2, '-');
								output.append(":");
								break;
							default:
								output.append(widths[col_id], '-');
								break;
							}
						}
						else {
							switch (align[col_id])
							{
							case 'l':
								output.append(":---");
								break;
							case 'r':
								output.append("---:");
								break;
							case 'c':
								output.append(":---:");
								break;
							default:
								output.append("---");
								break;
							}
						}
						if (col_id != col_number - 1 || ext_pipes)
							output.append("|");
					}
					first_line = false;
					output.append("\n");
				}
				col_id = 0;
			}
			cell_start = i + 1;
		}
	}
	return output;
}