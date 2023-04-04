#pragma once
#include "cnumpy.h"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <exception> 



class CSV_reader {

public:
    static std::vector<std::string> get_header(std::string line) {
        std::string delimiter = ",";
        size_t pos = 0;
        std::string token;
        while ((pos = line.find(delimiter)) != std::string::npos) {
            token = line.substr(0, pos);
            std::cout << token << std::endl;
            line.erase(0, pos + delimiter.length());
        }

        return std::vector<std::string>();
    }

	static Cnumpy read_csv_file_as_cnumpy(std::string path_to_file) {

        std::cout << "elo";
        std::ifstream newfile(path_to_file);
        std::string tpx;
        if (getline(newfile, tpx)) {
           // std::cout << tpx;
            get_header(tpx);
        }




       /* if (newfile.is_open()) {
            std::string tp;
            
            newfile.close(); 
        }
        else {
            std::cout << "blad";
           
        }*/

        return Cnumpy(2,2,std::vector<Type>());
	};
};
