#include "cnumpy.h"
#include <vector>
#include "type.h"
#include <iomanip>
#include <stdexcept>
#include "../Collection_Utility/Collection_Utility.h"
#include <bits/stdc++.h>

std::string Cnumpy::default_label = "*";
int Cnumpy::first_element_index = 0;


int Cnumpy::how_many_column_about_type(Type type) const {
    int column_about_type = 0;

    for (int i = 0; i < type_column.size(); ++i) {
        if (type_column[i] == type) {
            column_about_type++;
        }
    }
    return column_about_type;

}


int Cnumpy::position_actual_column_in_type(Type type, int index_column) const {
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
    int offset = (position_actual_column_in_type(type_column, column_index)) * y_dimension;
    return offset;
}

std::vector<Type> Cnumpy::get_type_columns() const {
    return type_column;
}

int Cnumpy::get_xy_int(int x, int y) const {
    if (type_column[x] == Type::integer_type) {
        int offset = (position_actual_column_in_type(Type::integer_type, x)) * y_dimension;
        return int_store[offset + y];
    } else {
        throw std::invalid_argument("The value of the column type does not match the value");
    }
}

std::string Cnumpy::get_xy_string(int x, int y) const {
    if (type_column[x] == Type::string_type) {
        int offset = (position_actual_column_in_type(Type::string_type, x)) * y_dimension;
        return string_store[offset + y];
    } else {
        throw std::invalid_argument("The value of the column type does not match the value");
    }
}

double Cnumpy::get_xy_double(int x, int y) const {
    if (type_column[x] == Type::double_type) {
        int offset = (position_actual_column_in_type(Type::double_type, x)) * y_dimension;
        return double_store[offset + y];
    } else {
        throw std::invalid_argument("The value of the column type does not match the value");
    }
}


void Cnumpy::set_xy(int x, int y, Cnumpy value) {

    if (value.get_type_columns()[0] == Type::integer_type) {
        int offset = (position_actual_column_in_type(Type::integer_type, x)) * y_dimension;
        int_store[offset + y] = value.get_xy_int(0, 0);
    } else if (value.get_type_columns()[0] == Type::double_type) {
        int offset = (position_actual_column_in_type(Type::double_type, x)) * y_dimension;
        double_store[offset + y] = value.get_xy_double(0, 0);
    } else {
        int offset = (position_actual_column_in_type(Type::string_type, x)) * y_dimension;
        string_store[offset + y] = value.get_xy_string(0, 0);
    }


}


void Cnumpy::set_xy(int x, int y, int value) {


    if (type_column[x] == Type::integer_type) {
        int offset = (position_actual_column_in_type(Type::integer_type, x)) * y_dimension;
        int_store[offset + y] = value;
    } else {
        throw std::invalid_argument("The value of the column type does not match the value");
    }


}

void Cnumpy::set_xy(int x, int y, std::string value) {

    if (type_column[x] == Type::string_type) {
        int offset = (position_actual_column_in_type(Type::string_type, x)) * y_dimension;
        string_store[offset + y] = value;
    } else {
        throw std::invalid_argument("The value of the column type does not match the value");
    }
}

void Cnumpy::set_xy(int x, int y, double value) {
    if (type_column[x] == Type::double_type) {
        int offset = (position_actual_column_in_type(Type::double_type, x)) * y_dimension;
        double_store[offset + y] = value;
    } else {
        throw std::invalid_argument("The value of the column type does not match the value");
    }
}


Cnumpy::Cnumpy(long x_dim, long y_dim, std::vector<Type> type_col, std::vector<std::string> nameCol) : Cnumpy(x_dim,
                                                                                                              y_dim,
                                                                                                              type_col) {
    name_column = nameCol;
}


Cnumpy::Cnumpy(long x_dim, long y_dim, std::vector<Type> type_col) {
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

                int position = obj.position_actual_column_in_type(Type::integer_type, x) * obj.y_dimension;

                os << std::left << symbolVerticalBreak << std::setw(obj.width_printed_value_on_sysout)
                   << obj.int_store[position + y];

            } else if (obj.type_column[x] == Type::double_type) {
                int position = obj.position_actual_column_in_type(Type::double_type, x) * obj.y_dimension;
                os << std::left << symbolVerticalBreak << std::setw(obj.width_printed_value_on_sysout)
                   << obj.double_store[position + y];
            } else {
                int position = obj.position_actual_column_in_type(Type::string_type, x) * obj.y_dimension;
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

                int position = obj.position_actual_column_in_type(Type::integer_type, x) * obj.y_dimension;

                os << std::left << symbolVerticalBreak << std::setw(obj.width_printed_value_on_sysout)
                   << obj.int_store[position + y];

            } else if (obj.type_column[x] == Type::double_type) {
                int position = obj.position_actual_column_in_type(Type::double_type, x) * obj.y_dimension;
                os << std::left << symbolVerticalBreak << std::setw(obj.width_printed_value_on_sysout)
                   << obj.double_store[position + y];
            } else {
                int position = obj.position_actual_column_in_type(Type::string_type, x) * obj.y_dimension;
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


Cnumpy Cnumpy::hist(int column_index, double bins) const {
    Type column_type = type_column[column_index];


    if (column_type != Type::string_type) {
        Cnumpy step = Cnumpy::of(bins);
        if (column_type == Type::integer_type) {
            int bins_as_int = (int) bins;
            step = Cnumpy::of(bins_as_int);
        }

        Cnumpy min_value = get_min_value_in_column(column_index);
        Cnumpy max_value = get_max_value_in_column(column_index);


        Cnumpy column_to_hist_values = (*this)[column_index];
        std::map<Cnumpy, int> histogram_values;


        while (min_value < max_value) {
            if (histogram_values.count(min_value) == 0) {
                histogram_values[min_value] = 0;
            } else {
                histogram_values[min_value] = histogram_values[min_value] + 1;
            }

            min_value = min_value + step;

        }

        for (int i = 0; i < column_to_hist_values.y_dimension; i++) {
            Cnumpy elem = column_to_hist_values[i];
            Cnumpy bucket_for_element = elem / step;
            histogram_values[bucket_for_element] = histogram_values[bucket_for_element] + 1;

        }


        std::vector<Type> type_column_histogram_cnumpy;
        type_column_histogram_cnumpy.push_back(column_type);
        type_column_histogram_cnumpy.push_back(Type::integer_type);

        std::vector<std::string> columns_name_histogram_cnumpy;
        columns_name_histogram_cnumpy.push_back("value");
        columns_name_histogram_cnumpy.push_back("quantity");


        std::vector<Cnumpy> key_hist_cnumpy;
        std::vector<int> value_count_cnumpy;

        for (const auto &entry: histogram_values) {
            key_hist_cnumpy.push_back(entry.first);
            value_count_cnumpy.push_back(entry.second);
        }

        Cnumpy results = Cnumpy(2, key_hist_cnumpy.size(), type_column_histogram_cnumpy, columns_name_histogram_cnumpy);
        results.set_column(0, key_hist_cnumpy);
        results.set_column(1, value_count_cnumpy);
        return results;
    } else {


        if (bins > 1 || bins < 0.95) {
            throw std::invalid_argument("For text, the division index cannot be different from 1");
        }

        Cnumpy column_to_hist_values = (*this)[column_index];
        std::map<Cnumpy, int> histogram_values;


        for (int i = 0; i < column_to_hist_values.y_dimension; i++) {

            if (histogram_values.count(column_to_hist_values[i]) == 0) {
                histogram_values[column_to_hist_values[i]] = 1;
            } else {
                histogram_values[column_to_hist_values[i]] = histogram_values[column_to_hist_values[i]] + 1;
            }


        }


        std::vector<Type> type_column_histogram_cnumpy;
        type_column_histogram_cnumpy.push_back(column_type);
        type_column_histogram_cnumpy.push_back(Type::integer_type);

        std::vector<std::string> columns_name_histogram_cnumpy;
        columns_name_histogram_cnumpy.push_back("value");
        columns_name_histogram_cnumpy.push_back("quantity");


        std::vector<Cnumpy> key_hist_cnumpy;
        std::vector<int> value_count_cnumpy;

        for (const auto &entry: histogram_values) {
            key_hist_cnumpy.push_back(entry.first);
            value_count_cnumpy.push_back(entry.second);
        }

        Cnumpy results = Cnumpy(2, key_hist_cnumpy.size(), type_column_histogram_cnumpy, columns_name_histogram_cnumpy);
        results.set_column(0, key_hist_cnumpy);
        results.set_column(1, value_count_cnumpy);

        return results;


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
    check_is_correct_one_element_cnumpys(obj, *this);
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
    check_is_correct_one_element_cnumpys(obj, *this);
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
    check_is_correct_one_element_cnumpys(obj, *this);
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
    check_is_correct_one_element_cnumpys(obj, *this);
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
    check_is_correct_one_element_cnumpys(obj, *this);
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
    check_is_correct_one_element_cnumpys(obj, *this);
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
        throw std::invalid_argument("Subtraction operation on two texts is prohibited");
    }

}

Cnumpy Cnumpy::operator/(Cnumpy &obj) const {
    check_is_correct_one_element_cnumpys(obj, *this);
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
        throw std::invalid_argument("Divide operation on two texts is prohibited");
    }

}


Cnumpy Cnumpy::operator*(Cnumpy &obj) const {
    check_is_correct_one_element_cnumpys(obj, *this);
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
        throw std::invalid_argument("Multiplication operation on two texts is forbidden");
    }

}

Cnumpy Cnumpy::operator-() const {
    check_is_correct_one_element_cnumpys(*this, *this);
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
        throw std::invalid_argument("Multiplication minus on  text is forbidden");
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
    if (get_x_dimension() == one_column) {
        int index_type_for_first_column = 0;
        Type type_col = type_column[index_type_for_first_column];
        if (type_col == Type::integer_type) {
            Cnumpy result_as_cnumpy = create_cnumpy_with_one_value(value, Type::integer_type, default_label);
            (*this) = result_as_cnumpy;
            return result_as_cnumpy;
        }else{
            throw std::invalid_argument("Assigned value have other type then cnumpy ");
        }
    }else{
        throw std::invalid_argument("Assign raw int to cnumpy is possible only for one column numpy");
    }
}

Cnumpy Cnumpy::operator=(double value){
    int one_column = 1;
    if (get_x_dimension() == one_column) {
        int index_type_for_first_column = 0;
        Type type_col = type_column[index_type_for_first_column];
        if (type_col == Type::double_type) {

            Cnumpy result_as_cnumpy = create_cnumpy_with_one_value(value, Type::double_type, default_label);
            (*this) = result_as_cnumpy;
            return result_as_cnumpy;
        }else{
            throw std::invalid_argument("Assigned value have other type then cnumpy ");
        }
    }else{
        throw std::invalid_argument("Assign raw string to cnumpy is possible only for one column numpy");
    }
}

Cnumpy Cnumpy::operator=(std::string value){
    int one_column = 1;
    if (get_x_dimension() == one_column) {
        int index_type_for_first_column = 0;
        Type type_col = type_column[index_type_for_first_column];
        if (type_col == Type::string_type) {
            Cnumpy result_as_cnumpy = create_cnumpy_with_one_value(value, Type::string_type, default_label);
            (*this) = result_as_cnumpy;
            return result_as_cnumpy;
        }else{
            throw std::invalid_argument("Assigned value have other type then cnumpy ");
        }
    }else{
        throw std::invalid_argument("Assign raw double to cnumpy is possible only for one column numpy");
    }
}




Cnumpy Cnumpy::operator=(std::vector<int> column_data){

    int one_column_array = 1;
    int first_column_index = 0;
    if (get_x_dimension() == one_column_array) {
        Type type_col = get_type_columns()[first_column_index];

        if (type_col == Type::integer_type) {
            Cnumpy column_cnumpy = create_cnumpy_with_one_column_from_raw_data(column_data, one_column_array,
                                                                               column_data.size(), type_col,default_label);
            (*this) = column_cnumpy;

            return *this;
        }else{
            throw std::invalid_argument("Assigned value have other type then cnumpy ");
        }

    }else{
        throw std::invalid_argument("Assign raw vector int to cnumpy is possible only for one column cnumpy");
    }
}

Cnumpy Cnumpy::operator=(std::vector<double> column_data ){
    int one_column_array = 1;
    int first_column_index = 0;
    if (get_x_dimension() == one_column_array) {
        Type type_col = get_type_columns()[first_column_index];

        if (type_col == Type::double_type) {

            Cnumpy column_cnumpy = create_cnumpy_with_one_column_from_raw_data(column_data, one_column_array,
                                                                               column_data.size(), type_col,
                                                                               default_label);
            (*this) = column_cnumpy;

            return *this;
        }else{
            throw std::invalid_argument("Assigned value have other type then cnumpy ");
        }

    }else{
        throw std::invalid_argument("Assign raw vector int to cnumpy is possible only for one column cnumpy");
    }
}

Cnumpy Cnumpy::operator=(std::vector<std::string> column_data){
    int one_column_array = 1;
    int first_column_index = 0;
    if (get_x_dimension() == one_column_array) {
        Type type_col = get_type_columns()[first_column_index];

        if (type_col == Type::string_type) {

            Cnumpy column_cnumpy = create_cnumpy_with_one_column_from_raw_data(column_data, one_column_array,
                                                                               column_data.size(), type_col,
                                                                               default_label);
            (*this) = column_cnumpy;

            return *this;
        }else{
            throw std::invalid_argument("Assigned value have other type then cnumpy ");
        }

    }else{
        throw std::invalid_argument("Assign raw vector int to cnumpy is possible only for one column cnumpy");
    }


}

Cnumpy Cnumpy::operator[](int index) const {

    int array_grether_then_1N = 1;
    int one_column_array = 1;
    if (get_x_dimension() > array_grether_then_1N) {
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




