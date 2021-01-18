// see header for documentation

#include "project.hpp"

#include "parser.hpp"

// #include "options.hpp"

#ifdef POSIX
	// checks if tty or pipe
	#include <stdio.h>
	#include <unistd.h>
#endif

char auto_detect_separator(const std::string& file, const char line_sep) {
	// no explicit separator given, tries to autodetect it in first parse
	// Selects the first that is constant across all lines
	// Else selects first that is present at least once and pads lines
	// Line sep needed to avoid conflicts
	std::string separators = "\t,;. "; // possible columns delimitors
	// remove line separator in case of conflicts
	for (unsigned char t = 0; t < separators.length(); ++t) {
		if (separators[t] == line_sep) {
			separators.erase(t, 1);
			break;
		}
	}
	unsigned char nb_separators = separators.length();

	unsigned int input_len = file.length();
	char * number_sep_per_line = new char[nb_separators];
	char * number_sep_per_current_line = new char[nb_separators];
	for (unsigned char j = 0; j < nb_separators; ++j) {
		number_sep_per_current_line[j] = 0;
		number_sep_per_line[j] = 0;
	}
	// only need to retain global -> if mismatch then invalid
	bool first_line = true;
	for (unsigned int i = 0; i < input_len; ++i) {
		if (file[i] == line_sep) {
			if (first_line) {
				// coppies current to global and reset current to 0
				char * t = number_sep_per_line;
				number_sep_per_line = number_sep_per_current_line;
				number_sep_per_current_line = t;
				first_line = false;
			}
			else
				for (unsigned char j = 0; j < nb_separators; ++j) {
					// printf("%d-%d ", number_sep_per_line[j], number_sep_per_current_line[j]);
					if (number_sep_per_current_line[j] != number_sep_per_line[j])
						number_sep_per_line[j] = -1; // mismatch, but not 0 occurrences
					number_sep_per_current_line[j] = 0;
				}
		}
		for (unsigned char j = 0; j < nb_separators; ++j) {
			if (file[i] == separators[j]) {
				++number_sep_per_current_line[j];
				break;
			}
		}
	}

	char col_sep;
	bool found = false;
	// first check, consistent candidate?
	for (unsigned char j = 0; j < nb_separators; ++j)
		if (number_sep_per_line[j] > 0) {
			found = true;
			col_sep = separators[j];
			break;
		}
	if (!found) {
		// second check, one appears ?
		for (unsigned char j = 0; j < nb_separators; ++j)
			if (number_sep_per_line[j] == -1) {
				found = true;
				col_sep = separators[j];
				break;
			}
		if (found)
			printf_warn("inconsistent number of column separator per line. Choose first candidate.\n");
		else {
			printf_error("no suitable column separators found. Tried the following:\n  ");
			for (unsigned char j = 0; j < nb_separators;) {
				if (separators[j] != '\t')
					std::fprintf(stderr, Color_Yellow "'%c'" Color_Reset, separators[j]);
				else
					std::fprintf(stderr, Color_Yellow "'\\t'" Color_Reset);
				std::fprintf(stderr, "%s", (++j < nb_separators) ? ", " : "\nYou can specify one with the '-c' argument.\n");
			}
			return 0;
		}
	}
	#ifdef POSIX
		if (isatty(fileno(stdout))) {
			if (col_sep != '\t')
				std::printf(NAME " selected '%c' as column separator\n", col_sep);
			else
				std::printf(NAME " selected '\\t' as column separator\n");
		}
	#else
		if (col_sep != '\t')
			std::printf(NAME " selected '%c' as column separator\n", col_sep);
		else
			std::printf(NAME " selected '\\t' as column separator\n");
	#endif
	delete number_sep_per_current_line;
	delete number_sep_per_line;
	return col_sep;
}

std::vector<unsigned int> columns_width(const std::string& file, const char col_sep, const char line_sep) {
	std::vector<unsigned int> widths;
	unsigned int input_len = file.length();
	unsigned int col_number = 0;
	unsigned int cell_start = 0;
	unsigned int table_width = 0; // length of width
	for (unsigned int t = 0; t < input_len; ++t) {
		if (file[t] == col_sep) {
			unsigned int width = t - cell_start;
			cell_start = t + 1;
			if (col_number < table_width)
				widths[col_number] = max(widths[col_number], width);
			else {
				widths.push_back(width);
				++table_width;
			}
			++col_number;
		}
		else if (file[t] == line_sep) {
			unsigned int width = t - cell_start;
			cell_start = t + 1;
			if (col_number < table_width)
				widths[col_number] = max(widths[col_number], width);
			else {
				widths.push_back(width);
				++table_width;
			}
			col_number = 0;
		}
	}
	return widths;
}

unsigned int table_width(const std::string& file, const char col_sep, const char line_sep) {
	unsigned int width = 0;
	unsigned int col_number = 0;
	unsigned int input_len = file.length();
	for (unsigned int t = 0; t < input_len; ++t) {
		if (file[t] == col_sep)
			++col_number;
		else if (file[t] == line_sep) {
			width = max(width, col_number+1);
			col_number = 0;
		}
	}
	return width;
}