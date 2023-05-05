#include "cnumpy.h"
#include <vector>
#include "type.h"
#include <iomanip>
#include <stdexcept>
#include "../Collection_Utility/Collection_Utility.h"

int Cnumpy::how_many_column_about_type(Type type) {
    int column_about_type = 0;

    for (int i = 0; i < type_column.size(); ++i) {
        if (type_column[i] == type) {
            column_about_type++;
        }
    }
    return column_about_type;

}


int Cnumpy::position_actual_column_in_type(Type type, int index_column) {
    int column_about_type = 0;

    for (int i = 0; i < type_column.size(); ++i) {

        if (type_column[i] == type && i < index_column) {
            column_about_type++;
        }
    }
    return column_about_type;
}

std::vector<std::string> Cnumpy::get_column_name(){
    return name_column;
}

int Cnumpy::get_x_dimension(){
    return x_dimension;
}


int Cnumpy::get_y_dimension(){
    return y_dimension;
}

std::vector<std::string> Cnumpy::get_column_string(int column_index) {
    int offset = offset_calculate(Type::string_type, column_index);
    return  std::vector<std::string>(string_store.begin() + offset, string_store.begin() + offset+y_dimension);
}

std::vector<double> Cnumpy::get_column_double(int column) {
    int offset = offset_calculate(Type::double_type,column);
    return  std::vector<double>(double_store.begin() + offset, double_store.begin() + offset+y_dimension);
}

std::vector<int> Cnumpy::get_column_int(int column) {
    int offset = offset_calculate(Type::integer_type,column);
    return  std::vector<int>(int_store.begin() + offset, int_store.begin() + offset+y_dimension);
}

int Cnumpy::offset_calculate(Type type_column,int column_index){
    int offset = (position_actual_column_in_type(type_column, column_index)) * y_dimension;
    return offset;
}

std::vector<Type> Cnumpy::get_type_columns() {
    return type_column;
}

int Cnumpy::get_xy_int(int x, int y){
    if (type_column[x] == Type::integer_type) {
        int offset = (position_actual_column_in_type(Type::integer_type, x)) * y_dimension;
        return int_store[offset + y];
    } else {
        throw std::invalid_argument("The value of the column type does not match the value");
    }
}

std::string Cnumpy::get_xy_string(int x, int y){
    if (type_column[x] == Type::string_type) {
        int offset = (position_actual_column_in_type(Type::string_type, x)) * y_dimension;
        return string_store[offset + y];
    } else {
        throw std::invalid_argument("The value of the column type does not match the value");
    }
}

double Cnumpy::get_xy_double(int x, int y){
    if (type_column[x] == Type::double_type) {
        int offset = (position_actual_column_in_type(Type::double_type, x)) * y_dimension;
        return double_store[offset + y] ;
    } else {
        throw std::invalid_argument("The value of the column type does not match the value");
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


Cnumpy::Cnumpy(long x_dim, long y_dim, std::vector<Type> type_col, std::vector<std::string> nameCol) : Cnumpy(x_dim,y_dim,type_col) {
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




Cnumpy Cnumpy::min_value(int column_index){
    Type type = type_column[column_index];
    if(type == Type::integer_type){
        std::vector<int> column_raw = get_column_int(column_index);
    }else if(type == Type::double_type){
        std::vector<double> column_raw = get_column_double(column_index);
    }else{
        std::vector<std::string> column_raw = get_column_string(column_index);
    }

}
Cnumpy Cnumpy::max_value(int column_index){

}


Cnumpy Cnumpy::hist(Cnumpy data,int column_index, int bins){

}


Cnumpy Cnumpy::get_unique_column_values(int column_index){

    Type column_type = type_column[column_index];
    std::string column_name = name_column[column_index];



    int y_dimension;
    int x_dimension = 1;
    if(column_type == Type::integer_type){
        std::set<int> unique_column_value = convertToSet(get_column_int(column_index));
        y_dimension = unique_column_value.size();
        std::vector<int> raw_column = convertToVector(unique_column_value);

        Cnumpy uniqued_cnumpy = create_cnumpy_with_one_column_from_raw_data(raw_column, x_dimension, y_dimension,
                                                                            column_type, column_name);
        return uniqued_cnumpy;


    }else if(column_type == Type::double_type){
        std::set<double> unique_column_value = convertToSet(get_column_double(column_index));
        y_dimension = unique_column_value.size();
        std::vector<double> raw_column = convertToVector(unique_column_value);

        Cnumpy uniqued_cnumpy = create_cnumpy_with_one_column_from_raw_data(raw_column, x_dimension, y_dimension,
                                                                            column_type, column_name);
        return uniqued_cnumpy;
    }else{
        std::set<std::string> unique_column_value = convertToSet(get_column_string(column_index));
        y_dimension = unique_column_value.size();
        std::vector<std::string> raw_column = convertToVector(unique_column_value);

        Cnumpy uniqued_cnumpy = create_cnumpy_with_one_column_from_raw_data(raw_column, x_dimension, y_dimension,
                                                                            column_type, column_name);
        return uniqued_cnumpy;
    }






}



