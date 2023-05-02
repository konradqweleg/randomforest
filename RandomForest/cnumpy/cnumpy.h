#ifndef cnumpy_h
#define cnumpy_h

#include <vector>
#include "type.h"

class Cnumpy {
//!! Utworz typ dla wartości xy wtedy mozna go zwracac lub wiersze !!!
private:

    std::vector<std::string> string_store = std::vector<std::string>();
    std::vector<double> double_store = std::vector<double>();
    std::vector<int> int_store = std::vector<int>();

    std::vector<Type> type_column = std::vector<Type>();

    std::vector<std::string> name_column = std::vector<std::string>();

    long x_dimension = 0;
    long y_dimension = 0;


    uint8_t width_printed_value_on_sysout = 20;


    int how_many_column_about_type(Type type);

    int position_actual_column_in_type(Type type, int index_column);


public:
    Cnumpy(long x_dim, long y_dim, std::vector<Type> typeCol);

    Cnumpy(long x_dim, long y_dim, std::vector<Type> typeCol, std::vector<std::string> nameCol);

    std::vector<std::string> get_column_name();

    std::vector<Type> get_type_columns();

    int offset_calculate(Type type_column, int column_index);

    std::vector<std::string> get_column_string(int column_index);

    std::vector<double> get_column_double(int column);

    std::vector<int> get_column_int(int column);


    int get_x_dimension();

    int get_y_dimension();

    void set_xy(int x, int y, int value);

    void set_xy(int x, int y, std::string value);

    void set_xy(int x, int y, double value);

    int get_xy_int(int x, int y);

    std::string get_xy_string(int x, int y);

    double get_xy_double(int x, int y);

    template<typename T>
    void set_column(long index_column, std::vector<T> column_values) {
        for (int i = 0; i < column_values.size(); ++i) {
            set_xy(index_column, i, column_values[i]);
        }
    };


    friend std::ostream &operator<<(std::ostream &os, Cnumpy &obj);


};


#endif
