//
// Created by konra on 25.04.2023.
//

#include "Files_utility.h"

int Files_utility::how_many_lines_in_file(std::string path_to_file) {
    std::ifstream in_file(path_to_file);
    const char new_line = '\n';
  //  int first_row_new_line = 1;
    int last_row_new_line = 1;
    int new_lines_symbol_to_adds = last_row_new_line;

    return std::count(std::istreambuf_iterator<char>(in_file),
                      std::istreambuf_iterator<char>(), new_line) + new_lines_symbol_to_adds;
}