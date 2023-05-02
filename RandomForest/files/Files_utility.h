//
// Created by konra on 25.04.2023.
//

#ifndef RANDOMFOREST_FILES_UTILITY_H
#define RANDOMFOREST_FILES_UTILITY_H

#include <fstream>
#include <algorithm>
#include <vector>
class Files_utility {

public:
    static int how_many_lines_in_file(std::string path_to_file);
    static void skip_n_lines_in_file(std::ifstream &file,int line_to_skip);
    static std::vector<std::string> read_all_lines_from_file(std::string path_to_file);

};


#endif //RANDOMFOREST_FILES_UTILITY_H
