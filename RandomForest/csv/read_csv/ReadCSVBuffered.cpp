//
// Created by Konrad on 01.05.2023.
//

#include "ReadCSVBuffered.h"


std::vector<std::string> ReadCSVBuffered::read_all_lines_from_file() {
    std::ifstream in_file(path_to_file);
    std::string read_lines;
    std::vector<std::string> raw_data;
    while (getline(in_file, read_lines)) {
        raw_data.push_back(read_lines);
    }

    in_file.close();
    return raw_data;
}

void ReadCSVBuffered::start_read() {
    lines_in_file = read_all_lines_from_file();
}


void ReadCSVBuffered::read_column_type() {

    std::string first_line_data = lines_in_file[1];
    std::vector<std::string> first_value_in_columns = Text_operation::split_by_delimiter(first_line_data,
                                                                                         delimiter);
    for (const std::string &column_value: first_value_in_columns) {
        type_columns.push_back(check_type(column_value));
    }


}

void ReadCSVBuffered::insert_data_to_cnumpy(){

    std::string line;
    int x_rows = 0;
    int y_columns = 0;


    int first_data_row_number = 1;
    for (int i = first_data_row_number; i < lines_in_file.size(); ++i) {

        std::vector<std::string> rows_value = Text_operation::split_by_delimiter(lines_in_file[i], delimiter);

        for (std::string value: rows_value) {

        std::string value_with_change_potential_double_format = convert_dot_double_value_below_one_on_correct_double_value(
                value
        );

        insert_value_to_cnumpy_with_convert_string_to_match_type(
                *result_cnumpy,
                value_with_change_potential_double_format,
                x_rows, y_columns
        );

            x_rows++;
        }
        x_rows = 0;
        y_columns++;
    }


}


void ReadCSVBuffered::create_empty_cnumpy()  {
    int columns_in_data = name_columns.size();
    int rows_data = lines_in_file.size() - 1;
    set_result_cnumpy(new Cnumpy(columns_in_data, rows_data, type_columns, name_columns));
}


void ReadCSVBuffered::read_column_name() {
    int first_line_in_file = 0;
    name_columns = Text_operation::split_with_remove_quote_by_delimiter(lines_in_file[first_line_in_file], delimiter);
}
