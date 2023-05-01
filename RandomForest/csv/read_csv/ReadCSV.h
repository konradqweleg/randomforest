//
// Created by Konrad on 01.05.2023.
//

#ifndef RANDOMFOREST_READCSV_H
#define RANDOMFOREST_READCSV_H

#include "cnumpy/cnumpy.h"
#include "text/Text_operation.h"

class ReadCSV {


public:
    ReadCSV() {}

    Cnumpy read_csv_as_cnumpy(std::string path_to_file_csv, std::string delimiter_in_csv) {
        path_to_file = path_to_file_csv;
        delimiter = delimiter_in_csv;

        start_read();
        read_column_name();
        read_column_type();
        create_empty_cnumpy();
        insert_data_to_cnumpy();
        end_read();

        return *result_cnumpy;
    }

protected:

    std::string path_to_file;

    std::string delimiter;

    Cnumpy *result_cnumpy = nullptr;

    void insert_value_to_cnumpy_with_convert_string_to_match_type(Cnumpy &data, std::string value, int x_rows,
                                                                  int y_columns) {

        std::vector<Type> type_column = data.get_type_columns();

        if (type_column[x_rows] == Type::integer_type) {
            data.set_xy(x_rows, y_columns, std::stoi(value));
        } else if (type_column[x_rows] == Type::double_type) {
            data.set_xy(x_rows, y_columns, std::stod(value));
        } else {
            data.set_xy(x_rows, y_columns, Text_operation::remove_quote_from_string(value));
        }
    }

    virtual void read_column_type() = 0;

    virtual void insert_data_to_cnumpy() = 0;

    virtual void create_empty_cnumpy() = 0;

    virtual void read_column_name() = 0;

    virtual void start_read() {};

    virtual void end_read() {};

    void set_result_cnumpy(Cnumpy *result) {
        result_cnumpy = result;
    }

    ~ReadCSV() {
        delete result_cnumpy;
    }


};


#endif //RANDOMFOREST_READCSV_H
