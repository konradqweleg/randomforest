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


class CSV_reader {
private:

    static std::string remove_quote_from_string(std::string text_to_remove_quote) {
        char quote = '\"';

        text_to_remove_quote.erase(
                std::remove(text_to_remove_quote.begin(), text_to_remove_quote.end(), quote),
                text_to_remove_quote.end()
        );

        return text_to_remove_quote;
    }


    static std::vector<std::string>
    split_string_by_delimiter(const std::string &text_to_split, const std::string &delimiter) {
        size_t pos_start = 0, pos_end, delim_len = delimiter.length();
        std::string token;
        std::vector<std::string> vector_split_by_delimiter_value;

        while ((pos_end = text_to_split.find(delimiter, pos_start)) != std::string::npos) {
            token = text_to_split.substr(pos_start, pos_end - pos_start);
            pos_start = pos_end + delim_len;
            vector_split_by_delimiter_value.push_back(token);
        }

        vector_split_by_delimiter_value.push_back(text_to_split.substr(pos_start));
        return vector_split_by_delimiter_value;
    }


    static std::vector<std::string> read_column_name_from_text_line(std::string line, std::string delimiter) {
        line = remove_quote_from_string(line);
        return split_string_by_delimiter(line, delimiter);
    }

    static std::vector<Type> read_column_type(const std::string &first_line_data, const std::string &delimiter) {
        std::vector<std::string> first_value_in_columns = split_string_by_delimiter(first_line_data, delimiter);
        std::vector<Type> type_columns = std::vector<Type>();

        for (const std::string &column_value: first_value_in_columns) {
            type_columns.push_back(check_type(column_value));
        }

        return type_columns;
    }

    static int how_many_lines_in_file(std::ifstream &in_file) {
        const char new_line = '\n';
        int first_row_new_line = 1;
        int last_row_new_line = 1;
        int new_lines_symbol_to_adds = first_row_new_line + last_row_new_line;

        return std::count(std::istreambuf_iterator<char>(in_file),
                          std::istreambuf_iterator<char>(), new_line) + new_lines_symbol_to_adds;
    }

    static void skip_header_rows_in_file(std::ifstream &in_file) {
        std::string skipped_line;
        getline(in_file, skipped_line);
    }

    static std::string
    convert_dot_double_value_below_one_on_correct_double_value(std::string text_with_potential_dot_double_value) {
        //sometimes user gives double as .2 thats mean 0.2 this functions converts format from .2 to 0.2 value
        const char dot_symbol = '.';
        int first_symbol_in_value = 0;

        if (text_with_potential_dot_double_value[first_symbol_in_value] == dot_symbol) {
            return "0" + text_with_potential_dot_double_value;
        } else {
            return text_with_potential_dot_double_value;
        }
    }

    static void insert_value_to_cnumpy_with_convert_string_to_match_type(Cnumpy &data, std::string value, int x_rows,
                                                                         int y_columns) {

        std::vector<Type> type_column = data.get_type_columns();

        if (type_column[x_rows] == Type::integer_type) {
            data.set_xy(x_rows, y_columns, std::stoi(value));
        } else if (type_column[x_rows] == Type::double_type) {
            data.set_xy(x_rows, y_columns, std::stod(value));
        } else {
            data.set_xy(x_rows, y_columns, remove_quote_from_string(value));
        }
    }

    static Cnumpy insert_data_to_cnumpy_from_file(Cnumpy &data, std::string file_path, std::string delimiter) {

        std::string line;
        int x_rows = 0;
        int y_columns = 0;


        std::ifstream file;
        file.open(file_path);


        skip_header_rows_in_file(file);


        while (getline(file, line)) {

            std::vector<std::string> rows_value = split_string_by_delimiter(line, delimiter);

            for (std::string value: rows_value) {

                std::string value_with_change_potential_double_format = convert_dot_double_value_below_one_on_correct_double_value(
                        value
                );

                insert_value_to_cnumpy_with_convert_string_to_match_type(
                        data,
                        value_with_change_potential_double_format,
                        x_rows, y_columns
                );

                x_rows++;
            }
            x_rows = 0;
            y_columns++;
        }


        return data;

    }


public:




    static Cnumpy read_csv_file_as_cnumpy(std::string path_to_file, std::string delimiter = ",") {


        std::ifstream in_file(path_to_file);
        std::string reads_line;


        std::vector<std::string> columns_name = std::vector<std::string>();

        if (getline(in_file, reads_line)) {
            columns_name = read_column_name_from_text_line(reads_line, delimiter);
        }


        int columns_in_data = columns_name.size();

        std::vector<Type> column_type = std::vector<Type>();
        if (getline(in_file, reads_line)) {
            column_type = read_column_type(reads_line, delimiter);
        }


        int rows_data = how_many_lines_in_file(in_file);


        in_file.close();

        Cnumpy data = Cnumpy(columns_in_data, rows_data, column_type, columns_name);


        // Reopen file in method below after count how many records is in data but probably ones open file is enought. Potential improvment
        Cnumpy result = insert_data_to_cnumpy_from_file(data, path_to_file, delimiter);


        return result;
    };
};
