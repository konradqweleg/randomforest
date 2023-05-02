//
// Created by Konrad on 01.05.2023.
//

#ifndef RANDOMFOREST_READCSV_EACHMETHODOPENCLOSEFILE_H
#define RANDOMFOREST_READCSV_EACHMETHODOPENCLOSEFILE_H

#include "ReadCSV.h"
#include <iostream>
#include <fstream>
#include "../../text/Text_operation.h"
#include "../../files/Files_utility.h"
#include <exception>

class ReadCSV_EachMethodOpenCloseFile : public ReadCSV {
private:
    std::string columns_name;
    const std::string ERROR_NO_ACCESS_TO_FILE = "Error reading data from file ";
    std::vector<Type> type_columns;
    std::vector<std::string> name_columns;

    void skip_header_rows_in_file(std::ifstream &in_file);

    std::vector<std::string> read_column_name_from_text_line(std::string line, std::string delimiter);


protected:

    void read_column_type() override;

    void read_column_name() override;

    void insert_data_to_cnumpy() override;

    void create_empty_cnumpy() override;


};


#endif //RANDOMFOREST_READCSV_EACHMETHODOPENCLOSEFILE_H
