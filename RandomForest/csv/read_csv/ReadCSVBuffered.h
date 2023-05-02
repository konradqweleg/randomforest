//
// Created by Konrad on 01.05.2023.
//

#ifndef RANDOMFOREST_READCSVBUFFERED_H
#define RANDOMFOREST_READCSVBUFFERED_H

#include "ReadCSV.h"
#include <fstream>
#include "text/Text_operation.h"

class ReadCSVBuffered : public ReadCSV {

private:
    std::vector<std::string> lines_in_file;

    std::vector<std::string> name_columns;

    std::vector<Type> type_columns = std::vector<Type>();


protected:

    void start_read() override;

    void read_column_type() override;

    void insert_data_to_cnumpy() override;

    void create_empty_cnumpy() override;

    void read_column_name() override;

};


#endif //RANDOMFOREST_READCSVBUFFERED_H
