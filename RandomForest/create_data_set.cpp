//
// Created by konra on 28.05.2023.
//

#include "create_data_set.h"

#include "create_data_set.h"
#include <cstdlib>

create_data_set::create_data_set()
{
    srand(NULL);
}

void create_data_set::create_files(int numberOfFiles, std::string read_file, int numberOfLine,std::string path_to_create_folders)
{
    std::vector < std::string > data = read_from_file(read_file);
    std::string firstLine = read_first_line(read_file);
    for (int i = 0; i < numberOfFiles; i++)
    {

        std::string dirname= path_to_create_folders +"/"+ std::to_string(i);
        const char* dir = dirname.data();

        struct stat sb;

        if (stat(dir, &sb) != 0) {
            _mkdir(dirname.data());
        }
        std::ofstream file(dirname + "/data.csv");
        if (file.is_open()) {


            std::vector < std::string > split_data_to_file = split_data(data, numberOfLine);
            file << firstLine << "\n";
            for (int j = 0; j < numberOfLine; j++)
            {
                file << split_data_to_file[j] << "\n";
            }
        }
        file.close();
    }
}

std::vector < std::string > create_data_set::read_from_file(std::string read_file)
{
    std::vector < std::string > data;
    std::ifstream file(read_file);
    if (file.is_open()) {

        std::string line;
        std::getline(file, line);
        while (std::getline(file, line)) {
            data.push_back(line);
        }
        file.close();
    }
    return data;
}

std::string create_data_set::read_first_line(std::string read_file)
{
    std::ifstream file(read_file);
    std::string line;
    if (file.is_open()) {
        std::getline(file, line);
        file.close();
    }
    return line;
}

void create_data_set::save_to_file(int fileName)
{
}

int create_data_set::randomValue(int min, int max)
{
    return rand() % (max - min) + min;

}

std::vector<std::string> create_data_set::split_data(std::vector<std::string> data, int numberOfLine)
{
    std::vector<std::string> splitData;

    for (int i = 0; i < numberOfLine; i++)
    {
        splitData.push_back(data[randomValue(0, data.size())]);
    }

    return splitData;
}
