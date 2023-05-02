#pragma once

#include "cnumpy/cnumpy.h"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <exception>
#include <algorithm>
#include "type.h"
#include <cstdlib>
#include <numeric>
#include <limits>
#include "../text/Text_operation.h"
#include "../files/Files_utility.h"
#include "read_csv/ReadCSV.h"
#include "read_csv/ReadCSVBuffered.h"
class csv {

private:
    ReadCSV* reader_csv = new ReadCSVBuffered();


public:
    Cnumpy read_cnumpy_from_csv(std::string path_to_file,std::string delimiter){
       return (*reader_csv).read_csv_as_cnumpy(path_to_file,delimiter);
    }


    csv(ReadCSV * csv_reader_mechanism = new ReadCSVBuffered()){
        reader_csv = csv_reader_mechanism;
    }

    ~csv(){
        delete reader_csv;
    }
};
