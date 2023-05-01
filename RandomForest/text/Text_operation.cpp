//
// Created by konra on 25.04.2023.
//

#include "Text_operation.h"

 std::string Text_operation::remove_quote_from_string(std::string text_to_remove_quote) {
    char quote = '\"';

    text_to_remove_quote.erase(
            std::remove(text_to_remove_quote.begin(), text_to_remove_quote.end(), quote),
            text_to_remove_quote.end()
    );

    return text_to_remove_quote;
}


 std::vector<std::string> Text_operation::split_by_delimiter(const std::string &text_to_split, const std::string &delimiter) {
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




std::vector<std::string> Text_operation::split_with_remove_quote_by_delimiter(std::string line, std::string delimiter) {
    line =  Text_operation::remove_quote_from_string(line);
    return Text_operation::split_by_delimiter(line, delimiter);
}