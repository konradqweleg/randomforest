#ifndef type_h
#define type_h

#include <string>
#include <iostream>
#include <limits>

enum Type {
    integer_type = 0,
    double_type = 1,
    string_type = 2,
    empty_type =3

};

static bool is_int(const std::string &text_with_potential_number) {

    for (char symbol_in_text: text_with_potential_number) {
        if (!std::isdigit(symbol_in_text)) {
            return false;
        }
    }
    return true;
}

static bool is_double(const std::string &text_with_potential_double) {
    char *end = nullptr;
    double value_as_double = strtod(text_with_potential_double.c_str(), &end);
    double max_double_value = std::numeric_limits<double>::max();
    return end != text_with_potential_double.c_str() && *end == '\0' && value_as_double != max_double_value;
}

static Type check_type(const std::string& value) {

    if (is_int(value)) {
        return Type::integer_type;
    } else if (is_double(value)) {
        return Type::double_type;
    } else {
        return Type::string_type;
    }

}


#endif
