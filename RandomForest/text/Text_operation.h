//
// Created by konra on 25.04.2023.
//

#ifndef RANDOMFOREST_TEXT_OPERATION_H
#define RANDOMFOREST_TEXT_OPERATION_H

#include <string>
#include <algorithm>
#include <vector>

class Text_operation {
public:
    static std::string remove_quote_from_string(std::string text_to_remove_quote);

    static std::vector<std::string>
    split_string_by_delimiter(const std::string &text_to_split, const std::string &delimiter);
};


#endif //RANDOMFOREST_TEXT_OPERATION_H
