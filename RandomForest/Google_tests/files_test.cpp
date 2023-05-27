//
// Created by konra on 25.04.2023.
//
#include "gtest/gtest.h"
#include <string>
#include "../files/Files_utility.h"
#include "../files/Files_utility.cpp"
#include <fstream>
#include <iostream>
#include "path_to_files.h"


TEST(test_files, how_many_lines_in_file) {

    int lines = Files_utility::how_many_lines_in_file(path_to_file::HOW_MANY_LINES);
    EXPECT_EQ(7,lines);

}


TEST(test_files,skip_n_line_in_files){
    std::ifstream in_file(path_to_file::HOW_MANY_LINES);
    Files_utility::skip_n_lines_in_file(in_file,3);

    int remain_lines = 0;
    std::string line = "";

    while(getline(in_file,line)){
        remain_lines ++;
    }

    in_file.close();
    EXPECT_EQ(4,remain_lines);

}


TEST(test_files,read_all_lines_from_file){
    std::vector<std::string> lines_from_file = Files_utility::read_all_lines_from_file(path_to_file::HOW_MANY_LINES);
    EXPECT_EQ(7,lines_from_file.size());

    int offset_number_numeration_in_file = 1;
    for(int i=0;i<lines_from_file.size();++i){
        int number_from_file_lines = stoi(lines_from_file[i]);
        EXPECT_EQ((i+offset_number_numeration_in_file),number_from_file_lines);
    }


}