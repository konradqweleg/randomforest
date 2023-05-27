#include "cnumpy.h"
#include <vector>
#include "type.h"
#include <iomanip>
#include <stdexcept>
#include "../Collection_Utility/Collection_Utility.h"
#include <bits/stdc++.h>

#include "math/histogram.h"
std::string Cnumpy::default_label = "*";
int Cnumpy::first_element_index = 0;
histogram * Cnumpy::histogram_calculator_strategy = nullptr;


 void Cnumpy::set_histogram_calculation_strategy(histogram  * hist_strategy) {
    throws_exception_when_null_pointer(hist_strategy);
    histogram_calculator_strategy = hist_strategy;
}


Cnumpy Cnumpy::hist(int column_index) const {
   throws_exception_when_null_pointer(histogram_calculator_strategy);
   return histogram_calculator_strategy->hist((*this), column_index);

}




int Cnumpy::how_many_column_about_type(Type type) const {
    int column_about_type = 0;

    for (int i = 0; i < type_column.size(); ++i) {
        if (type_column[i] == type) {
            column_about_type++;
        }
    }
    return column_about_type;

}


int Cnumpy::position_actual_column_in_same_column_type(Type type, int index_column) const {
    int column_about_type = 0;

    for (int i = 0; i < type_column.size(); ++i) {

        if (type_column[i] == type && i < index_column) {
            column_about_type++;
        }
    }
    return column_about_type;
}

std::vector<std::string> Cnumpy::get_column_name() const {
    return name_column;
}

int Cnumpy::get_x_dimension() const {
    return x_dimension;
}


int Cnumpy::get_y_dimension() const {
    return y_dimension;
}

std::vector<std::string> Cnumpy::get_column_string(int column_index) const {
    int offset = offset_calculate(Type::string_type, column_index);
    return std::vector<std::string>(string_store.begin() + offset, string_store.begin() + offset + y_dimension);
}

std::vector<double> Cnumpy::get_column_double(int column) const {
    int offset = offset_calculate(Type::double_type, column);
    return std::vector<double>(double_store.begin() + offset, double_store.begin() + offset + y_dimension);
}

std::vector<int> Cnumpy::get_column_int(int column) const {
    int offset = offset_calculate(Type::integer_type, column);
    return std::vector<int>(int_store.begin() + offset, int_store.begin() + offset + y_dimension);
}

int Cnumpy::offset_calculate(Type type_column, int column_index) const {
    int offset = (position_actual_column_in_same_column_type(type_column, column_index)) * y_dimension;
    return offset;
}

std::vector<Type> Cnumpy::get_type_columns() const {
    return type_column;
}

int Cnumpy::get_xy_int(int x, int y) const {
    throw_exception_when_access_to_no_exists_index(x,y);
    throw_exception_when_different_type(type_column[x],Type::integer_type);
    int offset_xy = calculate_position_xy_value_in_raw_store(x,y,Type::integer_type);
    return int_store[offset_xy];

}

std::string Cnumpy::get_xy_string(int x, int y) const {
    throw_exception_when_access_to_no_exists_index(x,y);
    throw_exception_when_different_type(type_column[x],Type::string_type);
    int offset_xy = calculate_position_xy_value_in_raw_store(x,y,Type::string_type);
    return string_store[offset_xy];
}

double Cnumpy::get_xy_double(int x, int y) const {
    throw_exception_when_access_to_no_exists_index(x,y);
    throw_exception_when_different_type(type_column[x],Type::double_type);
    int offset_xy = calculate_position_xy_value_in_raw_store(x,y,Type::double_type);
    return double_store[offset_xy];
}


void Cnumpy::set_xy(int x, int y, Cnumpy value) {
    int first_column_index = 0;
    throw_exception_when_access_to_no_exists_index(x,y,value);
    throw_exception_when_different_type(type_column[x],value.get_type_columns()[x]);


    if (value.get_type_columns()[first_column_index] == Type::integer_type) {
        int offset_xy = calculate_position_xy_value_in_raw_store(x,y,Type::integer_type);
        int_store[offset_xy] = value.get_xy_int(0, 0);
    } else if (value.get_type_columns()[first_column_index] == Type::double_type) {
        int offset_xy = calculate_position_xy_value_in_raw_store(x,y,Type::double_type);
        double_store[offset_xy] = value.get_xy_double(0, 0);
    } else {
        int offset_xy = calculate_position_xy_value_in_raw_store(x,y,Type::string_type);
        string_store[offset_xy] = value.get_xy_string(0, 0);
    }

}


void Cnumpy::set_xy(int x, int y, int value) {
    throw_exception_when_access_to_no_exists_index(x,y);
    throw_exception_when_different_type(type_column[x],Type::integer_type);
    int offset_xy = calculate_position_xy_value_in_raw_store(x,y,Type::integer_type);
    int_store[offset_xy] = value;

}

void Cnumpy::set_xy(int x, int y, std::string value) {
    throw_exception_when_access_to_no_exists_index(x,y);
    throw_exception_when_different_type(type_column[x],Type::string_type);
    int offset_xy = calculate_position_xy_value_in_raw_store(x,y,Type::string_type);
    string_store[offset_xy] = value;
}

void Cnumpy::set_xy(int x, int y, double value) {
    throw_exception_when_access_to_no_exists_index(x,y);
    throw_exception_when_different_type(type_column[x],Type::double_type);
    int offset_xy = calculate_position_xy_value_in_raw_store(x,y,Type::double_type);
    double_store[offset_xy] = value;
}


Cnumpy::Cnumpy(long x_dim, long y_dim, std::vector<Type> type_col, std::vector<std::string> nameCol) : Cnumpy(x_dim,
                                                                                                              y_dim,
                                                                                                              type_col) {
    name_column = nameCol;
}


Cnumpy::Cnumpy(long x_dim, long y_dim, std::vector<Type> type_col) {


    throws_exception_when_invalid_dimension_cnumpys(x_dim,y_dim);

    x_dimension = x_dim;
    y_dimension = y_dim;
    type_column = type_col;

    int how_many_int_type_column = how_many_column_about_type(Type::integer_type);
    for (int i = 0; i < how_many_int_type_column; ++i) {
        for (int x = 0; x < y_dim; ++x) {
            int_store.push_back(0);
        }
    }

    int how_many_double_type_column = how_many_column_about_type(Type::double_type);
    for (int i = 0; i < how_many_double_type_column; ++i) {
        for (int x = 0; x < y_dim; ++x) {
            double_store.push_back(0.0);
        }
    }

    int how_many_string_type_column = how_many_column_about_type(Type::string_type);
    for (int i = 0; i < how_many_string_type_column; ++i) {
        for (int x = 0; x < y_dim; ++x) {
            string_store.push_back("");
        }
    }


}


std::ostream &operator<<(std::ostream &os, Cnumpy &obj) {

    static const char *Type_as_text[] = {"Integer", "Double", "String"};
    char symbolVerticalBreak = '|';
    char symbolHorizontalBreak = '-';

    os << std::right << std::setw(obj.width_printed_value_on_sysout) << "";
    for (std::string name: obj.name_column) {
        os << std::left << symbolVerticalBreak << std::setw(obj.width_printed_value_on_sysout) << name << "";
    }
    os << std::endl;

    os << std::right << std::setw(obj.width_printed_value_on_sysout) << "";
    for (Type type: obj.type_column) {
        os << std::left << symbolVerticalBreak << std::setw(obj.width_printed_value_on_sysout) << Type_as_text[type]
           << "";
    }

    os << std::endl;
    os << std::right << std::setw(obj.width_printed_value_on_sysout) << "";
    for (int i = 0; i < obj.type_column.size(); ++i) {
        os << symbolVerticalBreak << std::left << std::setw(obj.width_printed_value_on_sysout) << i << "";
    }
    os << std::endl;

    for (int i = 0;
         i < obj.width_printed_value_on_sysout + (obj.x_dimension * obj.width_printed_value_on_sysout); ++i) {
        os << symbolHorizontalBreak;
    }

    os << std::endl;

    for (int y = 0; y < obj.y_dimension; y++) {
        os << std::left << std::setw(obj.width_printed_value_on_sysout) << y;
        for (int x = 0; x < obj.x_dimension; x++) {

            if (obj.type_column[x] == Type::integer_type) {

                int position = obj.position_actual_column_in_same_column_type(Type::integer_type, x) * obj.y_dimension;

                os << std::left << symbolVerticalBreak << std::setw(obj.width_printed_value_on_sysout)
                   << obj.int_store[position + y];

            } else if (obj.type_column[x] == Type::double_type) {
                int position = obj.position_actual_column_in_same_column_type(Type::double_type, x) * obj.y_dimension;
                os << std::left << symbolVerticalBreak << std::setw(obj.width_printed_value_on_sysout)
                   << obj.double_store[position + y];
            } else {
                int position = obj.position_actual_column_in_same_column_type(Type::string_type, x) * obj.y_dimension;
                os << std::left << symbolVerticalBreak << std::setw(obj.width_printed_value_on_sysout)
                   << obj.string_store[position + y];

            }


        }
        os << std::endl;
    }


    return os;
}

std::ostream &operator<<(std::ostream &os, Cnumpy &&obj) {

    static const char *Type_as_text[] = {"Integer", "Double", "String"};
    char symbolVerticalBreak = '|';
    char symbolHorizontalBreak = '-';

    os << std::right << std::setw(obj.width_printed_value_on_sysout) << "";
    for (std::string name: obj.name_column) {
        os << std::left << symbolVerticalBreak << std::setw(obj.width_printed_value_on_sysout) << name << "";
    }
    os << std::endl;

    os << std::right << std::setw(obj.width_printed_value_on_sysout) << "";
    for (Type type: obj.type_column) {
        os << std::left << symbolVerticalBreak << std::setw(obj.width_printed_value_on_sysout) << Type_as_text[type]
           << "";
    }

    os << std::endl;
    os << std::right << std::setw(obj.width_printed_value_on_sysout) << "";
    for (int i = 0; i < obj.type_column.size(); ++i) {
        os << symbolVerticalBreak << std::left << std::setw(obj.width_printed_value_on_sysout) << i << "";
    }
    os << std::endl;

    for (int i = 0;
         i < obj.width_printed_value_on_sysout + (obj.x_dimension * obj.width_printed_value_on_sysout); ++i) {
        os << symbolHorizontalBreak;
    }

    os << std::endl;

    for (int y = 0; y < obj.y_dimension; y++) {
        os << std::left << std::setw(obj.width_printed_value_on_sysout) << y;
        for (int x = 0; x < obj.x_dimension; x++) {

            if (obj.type_column[x] == Type::integer_type) {

                int position = obj.position_actual_column_in_same_column_type(Type::integer_type, x) * obj.y_dimension;

                os << std::left << symbolVerticalBreak << std::setw(obj.width_printed_value_on_sysout)
                   << obj.int_store[position + y];

            } else if (obj.type_column[x] == Type::double_type) {
                int position = obj.position_actual_column_in_same_column_type(Type::double_type, x) * obj.y_dimension;
                os << std::left << symbolVerticalBreak << std::setw(obj.width_printed_value_on_sysout)
                   << obj.double_store[position + y];
            } else {
                int position = obj.position_actual_column_in_same_column_type(Type::string_type, x) * obj.y_dimension;
                os << std::left << symbolVerticalBreak << std::setw(obj.width_printed_value_on_sysout)
                   << obj.string_store[position + y];

            }


        }
        os << std::endl;
    }


    return os;
}


Cnumpy Cnumpy::get_min_value_in_column(int column_index) const {
    std::string min_value_column_name = "min value";
    Type type = type_column[column_index];
    if (type == Type::integer_type) {

        std::vector<int> column_raw = get_column_int(column_index);
        int min_value = *min_element(column_raw.begin(), column_raw.end());
        Cnumpy result = create_cnumpy_with_one_value(min_value, Type::integer_type, min_value_column_name);
        return result;

    } else if (type == Type::double_type) {
        std::vector<double> column_raw = get_column_double(column_index);
        double min_value = *min_element(column_raw.begin(), column_raw.end());
        Cnumpy result = create_cnumpy_with_one_value(min_value, Type::double_type, min_value_column_name);
        return result;
    } else {
        std::vector<std::string> column_raw = get_column_string(column_index);
        std::string min_value = *min_element(column_raw.begin(), column_raw.end());
        Cnumpy result = create_cnumpy_with_one_value(min_value, Type::string_type, min_value_column_name);
        return result;
    }

}

Cnumpy Cnumpy::get_max_value_in_column(int column_index) const {
    std::string max_value_column_name = "max value";
    Type type = type_column[column_index];
    if (type == Type::integer_type) {
        std::vector<int> column_raw = get_column_int(column_index);
        int max_value = *max_element(column_raw.begin(), column_raw.end());
        Cnumpy result = create_cnumpy_with_one_value(max_value, Type::integer_type, max_value_column_name);
        return result;

    } else if (type == Type::double_type) {
        std::vector<double> column_raw = get_column_double(column_index);
        double max_value = *max_element(column_raw.begin(), column_raw.end());
        Cnumpy result = create_cnumpy_with_one_value(max_value, Type::double_type, max_value_column_name);
        return result;
    } else {
        std::vector<std::string> column_raw = get_column_string(column_index);
        std::string max_value = *max_element(column_raw.begin(), column_raw.end());
        Cnumpy result = create_cnumpy_with_one_value(max_value, Type::string_type, max_value_column_name);
        return result;
    }
}




Cnumpy Cnumpy::get_unique_column_values(int column_index) const {

    Type column_type = type_column[column_index];
    std::string column_name = name_column[column_index];


    int y_dimension;
    int x_dimension = 1;
    if (column_type == Type::integer_type) {
        std::set<int> unique_column_value = convertToSet(get_column_int(column_index));
        y_dimension = unique_column_value.size();
        std::vector<int> raw_column = convertToVector(unique_column_value);

        Cnumpy uniqued_cnumpy = create_cnumpy_with_one_column_from_raw_data(raw_column, x_dimension, y_dimension,
                                                                            column_type, column_name);
        return uniqued_cnumpy;


    } else if (column_type == Type::double_type) {
        std::set<double> unique_column_value = convertToSet(get_column_double(column_index));
        y_dimension = unique_column_value.size();
        std::vector<double> raw_column = convertToVector(unique_column_value);

        Cnumpy uniqued_cnumpy = create_cnumpy_with_one_column_from_raw_data(raw_column, x_dimension, y_dimension,
                                                                            column_type, column_name);
        return uniqued_cnumpy;
    } else {
        std::set<std::string> unique_column_value = convertToSet(get_column_string(column_index));
        y_dimension = unique_column_value.size();
        std::vector<std::string> raw_column = convertToVector(unique_column_value);

        Cnumpy uniqued_cnumpy = create_cnumpy_with_one_column_from_raw_data(raw_column, x_dimension, y_dimension,
                                                                            column_type, column_name);
        return uniqued_cnumpy;
    }


}




Cnumpy Cnumpy::of(int value) {
    return create_cnumpy_with_one_value(value, Type::integer_type, default_label);
}

Cnumpy Cnumpy::of(double value) {
    return create_cnumpy_with_one_value(value, Type::double_type, default_label);
}

Cnumpy Cnumpy::of(std::string value) {
    return create_cnumpy_with_one_value(value, Type::string_type, default_label);
}


Cnumpy::Cnumpy(int value) {

    (*this) =  create_cnumpy_with_one_value(value, Type::integer_type, default_label);
}

 Cnumpy::Cnumpy(double value) {

     (*this) = create_cnumpy_with_one_value(value, Type::double_type, default_label);
}

Cnumpy::Cnumpy(std::string value) {

     (*this) = create_cnumpy_with_one_value(value, Type::string_type, default_label);
}


Cnumpy Cnumpy::get_xy(int x, int y) const {

    throw_exception_when_access_to_no_exists_index(x,y);
    Type col_type = get_type_columns()[x];

    if (col_type == Type::integer_type) {
        int raw_value = get_xy_int(x, y);
        Cnumpy result = create_cnumpy_with_one_value(raw_value, col_type, default_label);
        return result;
    } else if (col_type == Type::double_type) {

        double raw_value = get_xy_double(x, y);
        Cnumpy result = create_cnumpy_with_one_value(raw_value, col_type, default_label);
        return result;
    } else {
        std::string raw_value = get_xy_string(x, y);
        Cnumpy result = create_cnumpy_with_one_value(raw_value, col_type, default_label);
        return result;
    }

}

bool Cnumpy::operator<(const Cnumpy &obj) const {
    throws_exception_when_cnumpys_have_more_than_one_element_or_differend_type(obj, *this);
    Type type_value = obj.get_type_columns()[first_element_index];

    if (type_value == Type::integer_type) {
        int my_value = get_xy_int(first_element_index, first_element_index);
        int other_value = obj.get_xy_int(first_element_index, first_element_index);
        return my_value < other_value;
    } else if (type_value == Type::double_type) {
        double my_value = get_xy_double(first_element_index, first_element_index);
        double other_value = obj.get_xy_double(first_element_index, first_element_index);
        return my_value < other_value;
    } else {
        std::string my_value = get_xy_string(first_element_index, first_element_index);
        std::string other_value = obj.get_xy_string(first_element_index, first_element_index);
        return my_value < other_value;
    }

}

bool Cnumpy::operator<=(Cnumpy &obj) const {
    throws_exception_when_cnumpys_have_more_than_one_element_or_differend_type(obj, *this);
    Type type_value = obj.get_type_columns()[first_element_index];

    if (type_value == Type::integer_type) {
        int my_value = get_xy_int(first_element_index, first_element_index);
        int other_value = obj.get_xy_int(first_element_index, first_element_index);
        return my_value <= other_value;
    } else if (type_value == Type::double_type) {
        double my_value = get_xy_double(first_element_index, first_element_index);
        double other_value = obj.get_xy_double(first_element_index, first_element_index);
        return my_value <= other_value;
    } else {
        std::string my_value = get_xy_string(first_element_index, first_element_index);
        std::string other_value = obj.get_xy_string(first_element_index, first_element_index);
        return my_value <= other_value;
    }

}

bool Cnumpy::operator>(Cnumpy &obj) const {

    Cnumpy &this_const = const_cast<Cnumpy &>(*this);

    if (obj != this_const) {
        return (!operator<(obj));
    } else {
        return false;
    }
}

bool Cnumpy::operator>=(Cnumpy &obj) const {
    throws_exception_when_cnumpys_have_more_than_one_element_or_differend_type(obj, *this);
    Type type_value = obj.get_type_columns()[first_element_index];

    if (type_value == Type::integer_type) {
        int my_value = get_xy_int(first_element_index, first_element_index);
        int other_value = obj.get_xy_int(first_element_index, first_element_index);
        return my_value >= other_value;
    } else if (type_value == Type::double_type) {
        double my_value = get_xy_double(first_element_index, first_element_index);
        double other_value = obj.get_xy_double(first_element_index, first_element_index);
        return my_value >= other_value;
    } else {
        std::string my_value = get_xy_string(first_element_index, first_element_index);
        std::string other_value = obj.get_xy_string(first_element_index, first_element_index);
        return my_value >= other_value;
    }
}


bool Cnumpy::operator==(Cnumpy &obj) const {
    throws_exception_when_cnumpys_have_more_than_one_element_or_differend_type(obj, *this);
    Type type_value = obj.get_type_columns()[first_element_index];

    if (type_value == Type::integer_type) {
        int my_value = get_xy_int(first_element_index, first_element_index);
        int other_value = obj.get_xy_int(first_element_index, first_element_index);
        return my_value == other_value;
    } else if (type_value == Type::double_type) {
        double my_value = get_xy_double(first_element_index, first_element_index);
        double other_value = obj.get_xy_double(first_element_index, first_element_index);

        return my_value == other_value;
    } else {
        std::string my_value = get_xy_string(first_element_index, first_element_index);
        std::string other_value = obj.get_xy_string(first_element_index, first_element_index);
        return my_value == other_value;
    }

}


bool Cnumpy::operator!=(Cnumpy &obj) const {
    return (!operator==(obj));
}


Cnumpy Cnumpy::operator+(Cnumpy &obj) const {
    throws_exception_when_cnumpys_have_more_than_one_element_or_differend_type(obj, *this);
    Type type_value = obj.get_type_columns()[first_element_index];

    if (type_value == Type::integer_type) {
        int my_value = get_xy_int(first_element_index, first_element_index);
        int other_value = obj.get_xy_int(first_element_index, first_element_index);
        int result = my_value + other_value;

        Cnumpy result_as_cnumpy = create_cnumpy_with_one_value(result, Type::integer_type, default_label);
        return result_as_cnumpy;
    } else if (type_value == Type::double_type) {
        double my_value = get_xy_double(first_element_index, first_element_index);
        double other_value = obj.get_xy_double(first_element_index, first_element_index);
        double result = my_value + other_value;

        Cnumpy result_as_cnumpy = create_cnumpy_with_one_value(result, Type::double_type, default_label);
        return result_as_cnumpy;
    } else {
        std::string my_value = get_xy_string(first_element_index, first_element_index);
        std::string other_value = obj.get_xy_string(first_element_index, first_element_index);
        std::string result = my_value + other_value;

        Cnumpy result_as_cnumpy = create_cnumpy_with_one_value(result, Type::string_type, default_label);
        return result_as_cnumpy;
    }

}

Cnumpy Cnumpy::operator-(Cnumpy &obj) const {
    throws_exception_when_cnumpys_have_more_than_one_element_or_differend_type(obj, *this);
    Type type_value = obj.get_type_columns()[first_element_index];

    if (type_value == Type::integer_type) {
        int my_value = get_xy_int(first_element_index, first_element_index);
        int other_value = obj.get_xy_int(first_element_index, first_element_index);
        int result = my_value - other_value;

        Cnumpy result_as_cnumpy = create_cnumpy_with_one_value(result, Type::integer_type, default_label);
        return result_as_cnumpy;
    } else if (type_value == Type::double_type) {
        double my_value = get_xy_double(first_element_index, first_element_index);
        double other_value = obj.get_xy_double(first_element_index, first_element_index);
        double result = my_value - other_value;

        Cnumpy result_as_cnumpy = create_cnumpy_with_one_value(result, Type::double_type, default_label);
        return result_as_cnumpy;
    } else {
        throw std::invalid_argument(Exception_Cnumpy_Message::TEXT_SUBTRACTION_OPERATION_IS_NOT_ALLOWED);
    }

}

Cnumpy Cnumpy::operator/(Cnumpy &obj) const {
    throws_exception_when_cnumpys_have_more_than_one_element_or_differend_type(obj, *this);
    Type type_value = obj.get_type_columns()[first_element_index];

    if (type_value == Type::integer_type) {
        int my_value = get_xy_int(first_element_index, first_element_index);
        int other_value = obj.get_xy_int(first_element_index, first_element_index);
        int result = my_value / other_value;

        Cnumpy result_as_cnumpy = create_cnumpy_with_one_value(result, Type::integer_type, default_label);
        return result_as_cnumpy;
    } else if (type_value == Type::double_type) {
        double my_value = get_xy_double(first_element_index, first_element_index);
        double other_value = obj.get_xy_double(first_element_index, first_element_index);
        double result = my_value / other_value;

        Cnumpy result_as_cnumpy = create_cnumpy_with_one_value(result, Type::double_type, default_label);
        return result_as_cnumpy;
    } else {
        throw std::invalid_argument(Exception_Cnumpy_Message::TEXT_DIVIDE_OPERATION_IS_NOT_ALLOWED);
    }

}


Cnumpy Cnumpy::operator*(Cnumpy &obj) const {
    throws_exception_when_cnumpys_have_more_than_one_element_or_differend_type(obj, *this);
    Type type_value = obj.get_type_columns()[first_element_index];

    if (type_value == Type::integer_type) {
        int my_value = get_xy_int(first_element_index, first_element_index);
        int other_value = obj.get_xy_int(first_element_index, first_element_index);
        int result = my_value * other_value;

        Cnumpy result_as_cnumpy = create_cnumpy_with_one_value(result, Type::integer_type, default_label);
        return result_as_cnumpy;
    } else if (type_value == Type::double_type) {
        double my_value = get_xy_double(first_element_index, first_element_index);
        double other_value = obj.get_xy_double(first_element_index, first_element_index);
        double result = my_value * other_value;

        Cnumpy result_as_cnumpy = create_cnumpy_with_one_value(result, Type::double_type, default_label);
        return result_as_cnumpy;
    } else {
        throw std::invalid_argument(Exception_Cnumpy_Message::TEXT_MULTIPLICATION_IS_NOT_ALLOWED);
    }

}

Cnumpy Cnumpy::operator-() const {
    throws_exception_when_cnumpys_have_more_than_one_element_or_differend_type(*this, *this);
    Type type_value = get_type_columns()[first_element_index];

    if (type_value == Type::integer_type) {
        int my_value = get_xy_int(first_element_index, first_element_index);

        int result = -my_value;

        Cnumpy result_as_cnumpy = create_cnumpy_with_one_value(result, Type::integer_type, default_label);
        return result_as_cnumpy;
    } else if (type_value == Type::double_type) {
        double my_value = get_xy_double(first_element_index, first_element_index);

        double result = -my_value;

        Cnumpy result_as_cnumpy = create_cnumpy_with_one_value(result, Type::double_type, default_label);
        return result_as_cnumpy;
    } else {
        throw std::invalid_argument(Exception_Cnumpy_Message::TEXT_NEGATION_IS_NOT_ALLOWED);
    }

}


Cnumpy Cnumpy::operator+=(Cnumpy& obj){
    (*this) =  (*this) + obj;
    return *this;
}

Cnumpy Cnumpy::operator-=(Cnumpy& obj){
    (*this) =  (*this) - (obj);
    return *this;
}

Cnumpy Cnumpy::operator/=(Cnumpy& obj){
    (*this) =  (*this) / obj;
    return *this;
}

Cnumpy Cnumpy::operator*=(Cnumpy& obj){
    (*this) =  (*this) * obj;
    return *this;
}

Cnumpy Cnumpy::operator=(int value){
    int one_column = 1;

    if ((get_x_dimension() == one_column) && (get_y_dimension()==1)) {

        int index_type_for_first_column = 0;
        Type type_col = type_column[index_type_for_first_column];
        if (type_col == Type::integer_type) {
            Cnumpy result_as_cnumpy = create_cnumpy_with_one_value(value, Type::integer_type, default_label);
            (*this) = result_as_cnumpy;
            return result_as_cnumpy;
        }else{
            throw std::invalid_argument(Exception_Cnumpy_Message::VALUE_TYPE_DO_NOT_MATCH);
        }
    }else{
        throw std::invalid_argument(Exception_Cnumpy_Message::OPERATION_ALLOWED_ONLY_FOR_SAME_MATRIX_DIMENSIONS);
    }
}

Cnumpy Cnumpy::operator=(double value){
    int one_column = 1;
    if (get_x_dimension() == one_column  && get_y_dimension()==1) {
        int index_type_for_first_column = 0;
        Type type_col = type_column[index_type_for_first_column];
        if (type_col == Type::double_type) {

            Cnumpy result_as_cnumpy = create_cnumpy_with_one_value(value, Type::double_type, default_label);
            (*this) = result_as_cnumpy;
            return result_as_cnumpy;
        }else{
            throw std::invalid_argument(Exception_Cnumpy_Message::VALUE_TYPE_DO_NOT_MATCH);
        }
    }else{
        throw std::invalid_argument(Exception_Cnumpy_Message::OPERATION_ALLOWED_ONLY_FOR_SAME_MATRIX_DIMENSIONS);
    }
}

Cnumpy Cnumpy::operator=(std::string value){
    int one_column = 1;
    if (get_x_dimension() == one_column  && get_y_dimension()==1) {

        int index_type_for_first_column = 0;
        Type type_col = type_column[index_type_for_first_column];
        if (type_col == Type::string_type) {
            Cnumpy result_as_cnumpy = create_cnumpy_with_one_value(value, Type::string_type, default_label);
            (*this) = result_as_cnumpy;
            return result_as_cnumpy;
        }else{
            throw std::invalid_argument(Exception_Cnumpy_Message::VALUE_TYPE_DO_NOT_MATCH);
        }
    }else{

        throw std::invalid_argument(Exception_Cnumpy_Message::OPERATION_ALLOWED_ONLY_FOR_SAME_MATRIX_DIMENSIONS);
    }
}




Cnumpy Cnumpy::operator=(std::vector<int> column_data){

    int one_column_array = 1;
    int first_column_index = 0;
    if (get_x_dimension() == one_column_array && get_y_dimension()==column_data.size()) {
        Type type_col = get_type_columns()[first_column_index];

        if (type_col == Type::integer_type) {
            Cnumpy column_cnumpy = create_cnumpy_with_one_column_from_raw_data(column_data, one_column_array,
                                                                               column_data.size(), type_col,default_label);
            (*this) = column_cnumpy;

            return *this;
        }else{
            throw std::invalid_argument(Exception_Cnumpy_Message::VALUE_TYPE_DO_NOT_MATCH);
        }

    }else{
        throw std::invalid_argument(Exception_Cnumpy_Message::OPERATION_ALLOWED_ONLY_FOR_SAME_MATRIX_DIMENSIONS);
    }
}

Cnumpy Cnumpy::operator=(std::vector<double> column_data ){
    int one_column_array = 1;
    int first_column_index = 0;
    if (get_x_dimension() == one_column_array && get_y_dimension()==column_data.size() ) {
        Type type_col = get_type_columns()[first_column_index];

        if (type_col == Type::double_type) {

            Cnumpy column_cnumpy = create_cnumpy_with_one_column_from_raw_data(column_data, one_column_array,
                                                                               column_data.size(), type_col,
                                                                               default_label);
            (*this) = column_cnumpy;

            return *this;
        }else{
            throw std::invalid_argument(Exception_Cnumpy_Message::VALUE_TYPE_DO_NOT_MATCH);
        }

    }else{
        throw std::invalid_argument(Exception_Cnumpy_Message::OPERATION_ALLOWED_ONLY_FOR_SAME_MATRIX_DIMENSIONS);
    }
}

Cnumpy Cnumpy::operator=(std::vector<std::string> column_data){
    int one_column_array = 1;
    int first_column_index = 0;
    if (get_x_dimension() == one_column_array && get_y_dimension()==column_data.size()) {
        Type type_col = get_type_columns()[first_column_index];

        if (type_col == Type::string_type) {

            Cnumpy column_cnumpy = create_cnumpy_with_one_column_from_raw_data(column_data, one_column_array,
                                                                               column_data.size(), type_col,
                                                                               default_label);
            (*this) = column_cnumpy;

            return *this;
        }else{
            throw std::invalid_argument(Exception_Cnumpy_Message::VALUE_TYPE_DO_NOT_MATCH);
        }

    }else{
        throw std::invalid_argument(Exception_Cnumpy_Message::OPERATION_ALLOWED_ONLY_FOR_SAME_MATRIX_DIMENSIONS);
    }


}

Cnumpy Cnumpy::operator[](int index) const {



    int array_grether_then_1N = 1;
    int one_column_array = 1;
    if (get_x_dimension() > array_grether_then_1N) {
        throw_exception_when_access_to_no_exists_index(index,0);
        Type type_col = type_column[index];

        if (type_col == Type::integer_type) {
            std::vector<int> column_with_integers = get_column_int(index);
            Cnumpy column_cnumpy = create_cnumpy_with_one_column_from_raw_data(column_with_integers, one_column_array,
                                                                               column_with_integers.size(), type_col,
                                                                               default_label);
            return column_cnumpy;
        } else if (type_col == Type::double_type) {
            std::vector<double> column_with_double = get_column_double(index);
            Cnumpy column_cnumpy = create_cnumpy_with_one_column_from_raw_data(column_with_double, one_column_array,
                                                                               column_with_double.size(), type_col,
                                                                               default_label);
            return column_cnumpy;
        } else {
            std::vector<std::string> column_with_string = get_column_string(index);
            Cnumpy column_cnumpy = create_cnumpy_with_one_column_from_raw_data(column_with_string, one_column_array,
                                                                               column_with_string.size(), type_col,
                                                                               default_label);
            return column_cnumpy;
        }

    } else {

        throw_exception_when_access_to_no_exists_index(0,index);
        int index_type_for_first_column = 0;
        Type type_col = type_column[index_type_for_first_column];
        if (type_col == Type::integer_type) {
            int value = get_xy_int(first_element_index, index);
            Cnumpy result_as_cnumpy = create_cnumpy_with_one_value(value, Type::integer_type, default_label);
            return result_as_cnumpy;
        } else if (type_col == Type::double_type) {
            double value = get_xy_double(first_element_index, index);
            Cnumpy result_as_cnumpy = create_cnumpy_with_one_value(value, Type::double_type, default_label);
            return result_as_cnumpy;
        } else {
            std::string value = get_xy_string(first_element_index, index);
            Cnumpy result_as_cnumpy = create_cnumpy_with_one_value(value, Type::string_type, default_label);
            return result_as_cnumpy;
        }


    }


}


Cnumpy Cnumpy::set(int value){

    throw_exception_when_different_type(type_column[0],Type::integer_type);

    if(get_x_dimension() == 1 && get_y_dimension() ==1){

        set_xy(0,0,value);
    }else{

        throw std::invalid_argument(Exception_Cnumpy_Message::OPERATION_ALLOWED_ONLY_FOR_SAME_MATRIX_DIMENSIONS);
    }
    return *this;
}
Cnumpy Cnumpy::set(double value){
    throw_exception_when_different_type(type_column[0],Type::double_type);
    if(get_x_dimension() == 1 && get_y_dimension() ==1){
        (*this) = create_cnumpy_with_one_value(value,Type::double_type,default_label);
    }else{
        throw std::invalid_argument(Exception_Cnumpy_Message::OPERATION_ALLOWED_ONLY_FOR_SAME_MATRIX_DIMENSIONS);
    }

    return *this;
}
Cnumpy Cnumpy::set(std::string value){
    throw_exception_when_different_type(type_column[0],Type::string_type);
    if(get_x_dimension() == 1 && get_y_dimension() ==1){
        (*this) = create_cnumpy_with_one_value(value,Type::string_type,default_label);
    }else{
        throw std::invalid_argument(Exception_Cnumpy_Message::OPERATION_ALLOWED_ONLY_FOR_SAME_MATRIX_DIMENSIONS);
    }
    return *this;
}

Cnumpy Cnumpy::set(std::vector<int> data){
    throw_exception_when_different_type(type_column[0],Type::integer_type);
    if(get_x_dimension() == 1 && get_y_dimension() == data.size() ){
        set_column(0,data);
    }else{
        throw std::invalid_argument(Exception_Cnumpy_Message::OPERATION_ALLOWED_ONLY_FOR_SAME_MATRIX_DIMENSIONS);
    }
    return *this;
}
Cnumpy Cnumpy::set(std::vector<double> data){
    throw_exception_when_different_type(type_column[0],Type::double_type);
    if(get_x_dimension() == 1 && get_y_dimension() == data.size() ){
        set_column(0,data);
    }else{
        throw std::invalid_argument(Exception_Cnumpy_Message::OPERATION_ALLOWED_ONLY_FOR_SAME_MATRIX_DIMENSIONS);
    }
    return *this;
}
Cnumpy Cnumpy::set(std::vector<std::string> data){
    throw_exception_when_different_type(type_column[0],Type::string_type);
    if(get_x_dimension() == 1 && get_y_dimension() == data.size() ){
        set_column(0,data);
    }else{
        throw std::invalid_argument(Exception_Cnumpy_Message::OPERATION_ALLOWED_ONLY_FOR_SAME_MATRIX_DIMENSIONS);
    }
    return *this;
}

Cnumpy Cnumpy::set(int x,int y,int value){
    set_xy(x,y,value);
    return *this;
}
Cnumpy Cnumpy::set(int x,int y,double value ){
    set_xy(x,y,value);
    return *this;
}
Cnumpy Cnumpy::set(int x,int y,std::string value){
    set_xy(x,y,value);
    return *this;
}

Cnumpy Cnumpy::set(int x,std::vector<int> data){

    if(get_y_dimension() == data.size() ){
        set_column(x,data);
    }else{
        throw std::invalid_argument(Exception_Cnumpy_Message::OPERATION_ALLOWED_ONLY_FOR_SAME_MATRIX_DIMENSIONS);
    }
    return *this;
}
Cnumpy Cnumpy::set(int x,std::vector<double> data){
    if( get_y_dimension() == data.size() ){
        set_column(x,data);
    }else{
        throw std::invalid_argument(Exception_Cnumpy_Message::OPERATION_ALLOWED_ONLY_FOR_SAME_MATRIX_DIMENSIONS);
    }
    return *this;
}
Cnumpy Cnumpy::set(int x,std::vector<std::string> data){
    if(get_y_dimension() == data.size() ){
        set_column(x,data);
    }else{
        throw std::invalid_argument(Exception_Cnumpy_Message::OPERATION_ALLOWED_ONLY_FOR_SAME_MATRIX_DIMENSIONS);
    }
    return *this;
}


Cnumpy Cnumpy::set(Cnumpy data) {

    if (data.get_x_dimension() == 1 && data.get_y_dimension() == 1 && get_x_dimension() == 1 && get_y_dimension() == 1) {
        throw_exception_when_different_type(type_column[0], data.get_type_columns()[0]);
        (*this) = data;

    }else{
        throw std::invalid_argument(Exception_Cnumpy_Message::OPERATION_ALLOWED_FOR_ONE_ELEMENT_CNUMPY);
    }


    return *this;
}
Cnumpy Cnumpy::set(int x,Cnumpy data) {

    if(x >= get_x_dimension()){
        throw std::invalid_argument(Exception_Cnumpy_Message::INDEXES_MUST_BE_SMALLER_THAN_DIMENSION_OF_CNUMPY);
    }else if(x < 0){
        throw std::invalid_argument(Exception_Cnumpy_Message::ACCESS_INDEX_MUST_BE_GREATER_OR_EQUAL_ZERO);
    }else {

        throw_exception_when_different_type(get_type_columns()[x], data.get_type_columns()[0]);

        if (data.get_x_dimension() == 1 && data.get_y_dimension() == get_y_dimension()) {

            Type type_column = get_type_columns()[x];

            if (type_column == Type::integer_type) {
                std::vector<int> raw_data = data.get_column_int(0);
                set_column(x, raw_data);
            } else if (type_column == Type::double_type) {
                std::vector<double> raw_data = data.get_column_double(0);
                set_column(x, raw_data);
            } else {
                std::vector<std::string> raw_data = data.get_column_string(0);
                set_column(x, raw_data);
            }

        } else {
            throw std::invalid_argument(Exception_Cnumpy_Message::OPERATION_ALLOWED_ONLY_FOR_SAME_MATRIX_DIMENSIONS);
        }
        return *this;
    }

}

Cnumpy Cnumpy::set(int x ,int y,Cnumpy value){
    Type type_column = get_type_columns()[x];

    if(type_column == Type::integer_type){
        int raw_Data = value.get_xy_int(0,0);
        set_xy(x,y,raw_Data);
    }else if(type_column == Type::double_type){
        double raw_Data = value.get_xy_double(0,0);
        set_xy(x,y,raw_Data);
    }else{
        std::string raw_Data = value.get_xy_string(0,0);
        set_xy(x,y,raw_Data);
    }
    return *this;
}

Cnumpy Cnumpy::of(std::vector<int> data) {
    Cnumpy result = create_cnumpy_with_one_column_from_raw_data(data,1,data.size(),Type::integer_type,default_label);
    return result;
}

Cnumpy Cnumpy::of(std::vector<double> data) {
    Cnumpy result = create_cnumpy_with_one_column_from_raw_data(data,1,data.size(),Type::double_type,default_label);
    return result;
}

Cnumpy Cnumpy::of(std::vector<std::string> data) {
    Cnumpy result = create_cnumpy_with_one_column_from_raw_data(data,1,data.size(),Type::string_type,default_label);
    return result;
}

Cnumpy::Cnumpy(std::vector<int>data) {

    Cnumpy result = create_cnumpy_with_one_column_from_raw_data(data,1,data.size(),Type::integer_type,default_label);
    (*this) = result;
}

Cnumpy::Cnumpy(std::vector<double>data) {

    Cnumpy result = create_cnumpy_with_one_column_from_raw_data(data,1,data.size(),Type::double_type,default_label);
    (*this) = result;
}

Cnumpy::Cnumpy(std::vector<std::string>data) {

    Cnumpy result = create_cnumpy_with_one_column_from_raw_data(data,1,data.size(),Type::string_type,default_label);
    (*this) = result;
}


void Cnumpy::throw_exception_when_cnumpy_has_more_then_one_element(Cnumpy data) {
    if (data.get_y_dimension() > 1 || data.get_x_dimension() > 1) {
        throw std::invalid_argument(Exception_Cnumpy_Message::OPERATION_ALLOWED_FOR_ONE_ELEMENT_CNUMPY);
    }
}

void Cnumpy::throw_exception_when_different_type_values(Cnumpy first_data, Cnumpy second_data) {
    std::vector<Type> first_types = first_data.get_type_columns();
    std::vector<Type> second_types = second_data.get_type_columns();

    for (int i = 0; i < first_types.size(); ++i) {
        if (first_types[i] != second_types[i]) {
            throw std::invalid_argument(Exception_Cnumpy_Message::VALUE_TYPE_DO_NOT_MATCH);
        }
    }
}

void Cnumpy::throw_exception_when_different_type(Type type_first,Type type_second){
    if (type_first == type_second) {

    } else {
        throw std::invalid_argument(Exception_Cnumpy_Message::VALUE_TYPE_DO_NOT_MATCH);
    }
}

 void Cnumpy::throws_exception_when_cnumpys_have_more_than_one_element_or_differend_type(Cnumpy data, Cnumpy data_2) {
    throw_exception_when_cnumpy_has_more_then_one_element(data);
    throw_exception_when_cnumpy_has_more_then_one_element(data_2);
    throw_exception_when_different_type_values(data, data_2);
}


bool Cnumpy::are_the_correct_dimensions_of_the_cnumpys(int x_dim,int y_dim){
    return (x_dim>0) && (y_dim>0);
}

void Cnumpy::throws_exception_when_invalid_dimension_cnumpys(int x_dim,int y_dim){
    bool is_correct_dimension = are_the_correct_dimensions_of_the_cnumpys(x_dim,y_dim);

    if(!is_correct_dimension){
        throw std::invalid_argument(Exception_Cnumpy_Message::BOTH_DIMENSION_MUST_BE_ABOVE_ZERO);
    }

}

void Cnumpy::throw_exception_when_access_to_no_exists_index(int x,int y,Cnumpy & data){
    if(x<0 || y<0){
        throw std::invalid_argument(Exception_Cnumpy_Message::ACCESS_INDEX_MUST_BE_GREATER_OR_EQUAL_ZERO);
    }

    if(data.get_x_dimension() <= x || data.get_y_dimension() <= y ){
        throw std::invalid_argument(Exception_Cnumpy_Message::INDEXES_MUST_BE_SMALLER_THAN_DIMENSION_OF_CNUMPY);
    }
}

void Cnumpy::throw_exception_when_access_to_no_exists_index(int x,int y) const{
    if(x<0 || y<0){
        throw std::invalid_argument(Exception_Cnumpy_Message::ACCESS_INDEX_MUST_BE_GREATER_OR_EQUAL_ZERO);
    }

    if(get_x_dimension() <= x || get_y_dimension() <= y ){
        throw std::invalid_argument(Exception_Cnumpy_Message::INDEXES_MUST_BE_SMALLER_THAN_DIMENSION_OF_CNUMPY);
    }
}



int Cnumpy::calculate_position_xy_value_in_raw_store(int x,int y, Type type_column) const {
    int offset_column = (position_actual_column_in_same_column_type(type_column, x)) * y_dimension;
    return offset_column + y;
}

int Cnumpy::count(int columns,Cnumpy value) const {
    int quantity = 0;

    if(get_x_dimension() > 1) {

        for (int i = 0; i < get_y_dimension(); ++i) {
            if ((*this)[columns][i] == value) {
                quantity++;
            }
        }

    }else{
        for (int i = 0; i < get_y_dimension(); ++i) {
            if ((*this)[i] == value) {
                quantity++;
            }
        }


    }
    return quantity;
}

Cnumpy Cnumpy::filter(int column_where_filter, Cnumpy filter_value) {
    int count_value = count(column_where_filter,filter_value);
    Cnumpy filtered_data = Cnumpy(get_x_dimension(), count_value, get_type_columns(), get_column_name());
    int filtered_i_index = 0;
    for(int i=0;i<get_y_dimension();++i){

        if((*this)[column_where_filter][i] == filter_value){

            for(int j=0;j<get_x_dimension();++j){
                Cnumpy value = (*this)[j][i];
                filtered_data.set(j,filtered_i_index,value);

            }
            filtered_i_index++;
        }

    }

    return filtered_data;
}


