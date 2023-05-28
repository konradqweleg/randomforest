#pragma once
#ifndef CREATE_DATA_SET
#define CREATE_DATA_SET
#include <iostream>
#include <cstdlib>
#include <filesystem>
#include <string>
#include <fstream>
#include <vector>
#include <direct.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <ctime>
class create_data_set
{
public:
    create_data_set();
    void create_files(int numberOfFiles, std::string read_file ,int numberOfLine,std::string path_to_create_folders);
    std::vector < std::string > read_from_file(std::string read_file);
    std::string read_first_line(std::string read_file);
    void save_to_file(int fileName);
    int randomValue(int min, int max);
    std::vector < std::string > split_data(std::vector < std::string > data, int numberOfLine);
};

#endif