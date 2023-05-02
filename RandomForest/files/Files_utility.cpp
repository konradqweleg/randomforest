//
// Created by konra on 25.04.2023.
//

#include "Files_utility.h"

int Files_utility::how_many_lines_in_file(std::string path_to_file) {
    std::ifstream in_file(path_to_file);
    const char new_line = '\n';
    int last_row_new_line = 1;
    int new_lines_symbol_to_adds = last_row_new_line;

    return std::count(std::istreambuf_iterator<char>(in_file),
                      std::istreambuf_iterator<char>(), new_line) + new_lines_symbol_to_adds;
}


void Files_utility::skip_n_lines_in_file(std::ifstream &file,int line_to_skip){
    std::string _;
    for(int i=0;i<line_to_skip;++i){
        getline(file,_);
    }
}

std::vector<std::string> Files_utility::read_all_lines_from_file(std::string path_to_file) {
    std::ifstream in_file(path_to_file);
    std::string read_lines;
    std::vector<std::string> raw_data;
    while (getline(in_file, read_lines)) {
        raw_data.push_back(read_lines);
    }

    in_file.close();
    return raw_data;
}