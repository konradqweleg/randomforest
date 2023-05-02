//
// Created by Konrad on 01.05.2023.
//

#include "ReadCSV_EachMethodOpenCloseFile.h"


void ReadCSV_EachMethodOpenCloseFile::skip_header_rows_in_file(std::ifstream &in_file) {
    std::string skipped_line;
    getline(in_file, skipped_line);
}


std::vector<std::string> ReadCSV_EachMethodOpenCloseFile::read_column_name_from_text_line(std::string line, std::string delimiter) {

    line = Text_operation::remove_quote_from_string(line);
    name_columns = Text_operation::split_by_delimiter(line, delimiter);
    return name_columns;

}


void ReadCSV_EachMethodOpenCloseFile::read_column_type() {

    std::ifstream in_file(path_to_file);
    std::string first_line_data;
    Files_utility::skip_n_lines_in_file(in_file, 1);

    if (!getline(in_file, first_line_data)) {
        throw new std::runtime_error(ERROR_NO_ACCESS_TO_FILE + path_to_file);
    }

    std::vector<std::string> first_value_in_columns = Text_operation::split_by_delimiter(first_line_data, delimiter);

    for (const std::string &column_value: first_value_in_columns) {
        type_columns.push_back(check_type(column_value));
    }
}

void ReadCSV_EachMethodOpenCloseFile::read_column_name() {
    std::ifstream in_file(path_to_file);

    std::string reads_line;

    if (getline(in_file, reads_line)) {
        read_column_name_from_text_line(reads_line, delimiter);
    } else {
        throw new std::runtime_error(ERROR_NO_ACCESS_TO_FILE + path_to_file);
    }

    in_file.close();

}


void ReadCSV_EachMethodOpenCloseFile::insert_data_to_cnumpy() {

    std::string line;
    int x_rows = 0;
    int y_columns = 0;


    std::ifstream file;
    file.open(path_to_file);


    skip_header_rows_in_file(file);


    while (getline(file, line)) {

        std::vector<std::string> rows_value = Text_operation::split_by_delimiter(line, delimiter);

        for (std::string value: rows_value) {

            std::string value_with_change_potential_double_format = convert_dot_double_value_below_one_on_correct_double_value(
                    value);

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


void ReadCSV_EachMethodOpenCloseFile::create_empty_cnumpy() {

    int columns_in_data = name_columns.size();
    int rows_data = Files_utility::how_many_lines_in_file(path_to_file) - 1;
    set_result_cnumpy(new Cnumpy(columns_in_data, rows_data, type_columns, name_columns));

}