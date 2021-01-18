// see header for doc

#include "project.hpp"

#include "options.hpp"

bool use_padding     = true;
bool ext_pipes       = true;
bool auto_detect_sep = true;
char col_sep         = '\t';
char line_sep        = '\n';
char * in_path       = nullptr;
char * out_path      = nullptr;
std::vector<char> align;

int parse_cmd(int argc, char ** argv) {
  // Command-line parsing
  bool show_help = false;
  bool show_version = false;
  bool changed_line = false;
  // argv[0] is program name
  for (int i = 1; i < argc; ++i) {
    std::string arg = argv[i];
    if (arg == "-h" || arg == "--help" || arg == "-help") {
      // help
      show_help = true;
    }
    else if (arg == "-v" || arg == "--version" || arg == "-version") {
      // version
      show_version = true;
    }
    else if (arg == "-i") {
      // in file
      if (in_path == nullptr) {
        if (++i == argc) {
          printf_error("no file name after \"-i\" argument.\n");
          return 1;
        }
        in_path = argv[i];
      } else {
          printf_error("multiple input files specified with \"-i\".\n");
          return 1;       
      }
    }
    else if (arg == "-o") {
      // out file
      if (out_path == nullptr) {
        if (++i == argc) {
          printf_error("no file name after \"-o\" argument.\n");
          return 1;
        }
        out_path = argv[i];
      } else {
        printf_error("multiple output files specified with \"-o\".\n");
        return 1;       
      }
    }
    else if (arg == "-a") { 
      // column alignement
      if (++i == argc) {
        printf_error("no alignement string after \"-a\" argument.\n");
        return 1;
      }
      unsigned int j = 0;
      while (argv[i][j]) {
        switch (argv[i][j])
        {
        case 'l':
        case 'c':
        case 'r':
        case '_':
          align.push_back(argv[i][j]);
          break;
        default:
          printf_error("alignement string must only have 'l', 'c', 'r' or '_'\n  (left, center, right or none) as characters. Not '%c'.\n", argv[i][j]);
          return 1;
        }
        ++j;
      }
    }
    else if (arg == "-c") {
      // column separator
      if (auto_detect_sep) {
        if (++i == argc) {
          printf_error("no column separation character after \"-c\" argument.\n");
          return 1;
        }
        if (argv[i][1] != 0) {
          printf_error("the column separation character must be a char, not \"%s\".\n", argv[i]);
          return 1;
        }
        auto_detect_sep = false;
        col_sep = argv[i][0];
      }
      else {
        printf_error("multiple column separators specified with \"-c\".\n");
        return 1;           
      }
    }
    else if (arg == "-l") {
      // line separator
      if (changed_line) {
        printf_error("multiple line separators specified with \"-l\".\n");
        return 1;
      }
      if (++i == argc) {
        printf_error("no line separation character after \"-l\" argument.\n");
        return 1;
      }
      if (argv[i][1] != 0) {
        printf_error("the line separation character must be a char, not \"%s\".\n", argv[i]);
        return 1;          
      }
      changed_line = true;
      line_sep = argv[i][0];
    }
    else if (arg == "-no-pad") {
      use_padding = false;
    }
    else if (arg == "-no-pipes") {
      ext_pipes = false;
    }
    else {
      // unknown option
      printf_error("unknown argument \"%s\"\n  use --help for a list of valid arguments.\n", arg.c_str());
      return 1;
    }
  }
  if (show_help) {
    printf("%s (version %s) generates markdown table from csv file\n", NAME, VERSION);
    printf("  Options:\n");
    printf("    %s-i <file>%s    input file in csv format. Read standard input if absent\n", Color_Orange, Color_Reset);
    printf("    %s-o <file>%s    output file. Print to standard output if absent\n", Color_Orange, Color_Reset);
    printf("    %s-a <str>%s     column alignement (string of 'l', 'c', 'r', '_')\n", Color_Orange, Color_Reset);
    printf("    %s-c <char>%s    column separation character, attempts to autodetermine if absent\n", Color_Orange, Color_Reset);
    printf("    %s-l <char>%s    line separation character, default is \\n\n", Color_Orange, Color_Reset);
    printf("    %s-no-pad%s      don't autopad columns to have same width\n", Color_Orange, Color_Reset);
    printf("    %s-no-pipes%s    don't place external pipes\n", Color_Orange, Color_Reset);
    printf("    %s-h --help%s    show this help\n", Color_Orange, Color_Reset);
    printf("    %s-v --version%s show version number\n", Color_Orange, Color_Reset);
    printf("\n");
    return -1;
  } else if (show_version) {
    printf("%s version %s\n", NAME, VERSION);
    return -1;
  }

  if (changed_line) {
    if (!auto_detect_sep && col_sep == line_sep) {
      printf_error("same line and column separator '%c'.", col_sep);
      return 1;
    }
  }
  else if (!auto_detect_sep && col_sep == '\n') {
    printf_error("'\\n' is the default line separator.\n  specify another with '-l' if you want to use it as column separator");
    return 1;    
  }
  return 0;
}