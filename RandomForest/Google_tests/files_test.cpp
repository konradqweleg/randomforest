//
// Created by konra on 25.04.2023.
//
#include "gtest/gtest.h"
#include <string>
#include "../files/Files_utility.h"
#include "../files/Files_utility.cpp"
#include <fstream>
TEST(test_text_operation, how_many_lines_in_file) {

    std::string path_to_file = "C:\\Users\\konra\\Documents\\PVM_Projekt\\randomforest\\RandomForest\\Google_tests\\test_data\\how_many_lines_data_for_test.txt";
    std::ifstream in_file(path_to_file);
    int lines = Files_utility::how_many_lines_in_file(in_file);
    EXPECT_EQ(7,lines);

}