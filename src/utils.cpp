#include <getopt.h>
#include <stdlib.h>
#include <iostream>
#include <iomanip>

#include "utils.h"

using namespace std;

program_args::program_args()
  : allowed_edit_distance(0),
    pattern_file(0),
    patterns(0),
    help_flag(false),
    source_text_files(0) { }

program_args get_program_parameters(int argc, char** argv) {
  int option_index;
  int current_parameter;
  program_args args;

  struct option long_options[] =
  {
    {"edit",    required_argument, 0, 'e'},
    {"pattern", required_argument, 0, 'p'},
    {"help",    no_argument,       0, 'h'},
    {0, 0, 0, 0}
  };

  while (1) {
    current_parameter = getopt_long(argc, argv, "e:p:h", long_options, &option_index);

    if (current_parameter == -1) {
      break;
    }

    switch (current_parameter) {
      case 0:
      // No momento, nenhum argumento está sendo usado para setar uma flag
      break;
      case 'e':
      args.allowed_edit_distance = atoi(optarg);
      break;
      case 'p':
      args.pattern_file = optarg;
      break;
      case 'h':
      args.help_flag = true;
      break;
      case '?':
      // Um argumento desconhecido é apenas ignorado no momento
      break;
      default:
      abort();
    }
  }

  if (optind < argc) {
    /* If pattern_flag is set, then the remaining arguments
    are target textfiles. Otherwise, the first one will be
    the pattern string*/
    if (!args.pattern_file) {
      args.patterns = new char*[2];
      args.patterns[0] = argv[optind++];
      args.patterns[1] = 0;
    }

    if (optind < argc) {
      int source_text_files_length = argc - optind + 2;
      int i = 0;

      args.source_text_files = new char*[source_text_files_length];

      while (optind < argc) {
        args.source_text_files[i++] = argv[optind++];
      }

      args.source_text_files[i] = 0;
    }
  }

  return args;
}

void print_help_line(char const *msg1, char const *msg2) {
  cout << left << setw(35) << msg1 << setw(45) << msg2 << endl;
}

void print_help_text() {
  cout << "Usage: pmt [options] [pattern] textfilepath [textfilepath ...]" << endl;
  cout << "Options:" << endl;
  print_help_line("  -e, --edit=<edit distance>", "Sets allowed edit distance for approximated text search");
  print_help_line("  -p, --pattern=<pattern file>","Specifies file from which the program should read the patterns to be used (each line of the file specifies a pattern)");
  print_help_line("  -h, --help","Shows this message");
  cout << endl << "  If a pattern file is not specified, the first argument given to pmt will be read as the only pattern to be searched for in the text file. Several source text files can be specified at the same time." << endl;
}
