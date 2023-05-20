#ifndef cnumpy_h
#define cnumpy_h

#include <vector>
#include "type.h"
#include "Exception_Cnumpy_Message.h"


#include <memory>

/*
 * Warning this version Cnumpy operator [] use copy semantic so you shouldn't useage it to assign use method set
 */
/*Do zrobienia
 *  metoda na nazwe kolumny i typ
 */
class histogram;
class histogram_base;




class Cnumpy {
private:

    static std::string default_label;
    static int first_element_index;




    std::vector<std::string> string_store = std::vector<std::string>();
    std::vector<double> double_store = std::vector<double>();
    std::vector<int> int_store = std::vector<int>();

    std::vector<Type> type_column = std::vector<Type>();

    std::vector<std::string> name_column = std::vector<std::string>();

    long x_dimension = 0;
    long y_dimension = 0;

    uint8_t width_printed_value_on_sysout = 20;


    int how_many_column_about_type(Type type) const;

    int position_actual_column_in_same_column_type(Type type, int index_column) const;



    static histogram* histogram_calculator_strategy;


    static void throws_exception_when_null_pointer(void * ptr){
        if(ptr == nullptr){
            throw std::invalid_argument(Exception_Cnumpy_Message::NULL_POINTER_STRATEGY);
        }
    }

    template<typename T>
    static Cnumpy
    create_cnumpy_with_one_column_from_raw_data(std::vector<T> raw_column_data, int x_dim, int y_dim, Type column_type,
                                                std::string &column_name) {
        std::vector<std::string> name_columns;
        name_columns.push_back(column_name);

        std::vector<Type> type_columns;
        type_columns.push_back(column_type);

        Cnumpy one_column_cnumpy = Cnumpy(x_dim, y_dim, type_columns, name_columns);
        one_column_cnumpy.set_column(0, raw_column_data);

        return one_column_cnumpy;
    }


    template<typename T>
    static Cnumpy create_cnumpy_with_one_value(T raw_value, Type column_type, std::string &column_name) {
        std::vector<std::string> name_columns;
        name_columns.push_back(column_name);

        std::vector<Type> type_columns;
        type_columns.push_back(column_type);

        Cnumpy cnumpy_one_value = Cnumpy(1, 1, type_columns, name_columns);

        std::vector<T> data;
        data.push_back(raw_value);


        cnumpy_one_value.set_column(0, data);

        return cnumpy_one_value;
    }


    static void throw_exception_when_cnumpy_has_more_then_one_element(Cnumpy data);

    static void throw_exception_when_different_type_values(Cnumpy first_data, Cnumpy second_data);

    static void throw_exception_when_different_type(Type type_first,Type type_second);

    static void throws_exception_when_cnumpys_have_more_than_one_element_or_differend_type(Cnumpy data, Cnumpy data_2);

    bool are_the_correct_dimensions_of_the_cnumpys(int x_dim,int y_dim);

    void throws_exception_when_invalid_dimension_cnumpys(int x_dim,int y_dim);

    void throw_exception_when_access_to_no_exists_index(int x,int y,Cnumpy & data);

    void throw_exception_when_access_to_no_exists_index(int x,int y)const;

    int calculate_position_xy_value_in_raw_store(int x,int y, Type type_column) const ;

    int offset_calculate(Type type_column, int column_index) const;

public:

    static void set_histogram_calculation_strategy(histogram  * hist_strategy);

    static Cnumpy of(int value);

    static Cnumpy of(double value);

    static Cnumpy of(std::string value);

    static Cnumpy of(std::vector<int> value);

    static Cnumpy of(std::vector<double> value);

    static Cnumpy of(std::vector<std::string> value);


    Cnumpy set(int);

    Cnumpy set(double);

    Cnumpy set(std::string);

    Cnumpy set(std::vector<int>);

    Cnumpy set(std::vector<double>);

    Cnumpy set(std::vector<std::string>);

    Cnumpy set(int, int, int);

    Cnumpy set(int, int, double);

    Cnumpy set(int, int, std::string);

    Cnumpy set(int, std::vector<int>);

    Cnumpy set(int, std::vector<double>);

    Cnumpy set(int, std::vector<std::string>);

    Cnumpy set(Cnumpy);

    Cnumpy set(int, Cnumpy);

    Cnumpy set(int, int, Cnumpy);

    void set_xy(int x, int y, int value);

    void set_xy(int x, int y, std::string value);

    void set_xy(int x, int y, double value);

    void set_xy(int x, int y, Cnumpy value);

    template<typename T>
    void set_column(long index_column, std::vector<T> column_values) {

        int first_y_index = 0;
        throw_exception_when_access_to_no_exists_index(index_column,first_y_index,*this);

        for (int i = 0; i < column_values.size(); ++i) {
            set_xy(index_column, i, column_values[i]);
        }
    };


    bool operator<(const Cnumpy &obj) const;

    bool operator<=(Cnumpy &obj) const;

    bool operator>(Cnumpy &obj) const;


    bool operator>=(Cnumpy &obj) const;


    bool operator==(Cnumpy &obj) const;

    bool operator!=(Cnumpy &obj) const;


    Cnumpy operator+(Cnumpy &obj) const;

    Cnumpy operator-(Cnumpy &obj) const;

    Cnumpy operator/(Cnumpy &obj) const;


    Cnumpy operator*(Cnumpy &obj) const;

    Cnumpy operator-() const;

    Cnumpy operator[](int index) const;

    Cnumpy operator+=(Cnumpy &obj);

    Cnumpy operator-=(Cnumpy &obj);

    Cnumpy operator/=(Cnumpy &obj);

    Cnumpy operator*=(Cnumpy &obj);


    Cnumpy operator=(int);

    Cnumpy operator=(double);

    Cnumpy operator=(std::string);

    Cnumpy operator=(std::vector<int>);

    Cnumpy operator=(std::vector<double>);

    Cnumpy operator=(std::vector<std::string>);


    Cnumpy(int value);

    Cnumpy(double value);

    Cnumpy(std::string value);

    Cnumpy(std::vector<int>);

    Cnumpy(std::vector<double>);

    Cnumpy(std::vector<std::string>);

    Cnumpy(long x_dim, long y_dim, std::vector<Type> typeCol);

    Cnumpy(long x_dim, long y_dim, std::vector<Type> typeCol, std::vector<std::string> nameCol);

    std::vector<std::string> get_column_name() const;

    std::vector<Type> get_type_columns() const;

    std::vector<std::string> get_column_string(int column_index) const;

    std::vector<double> get_column_double(int column) const;

    std::vector<int> get_column_int(int column) const;


    int get_x_dimension() const;

    int get_y_dimension() const;


    int get_xy_int(int x, int y) const;

    std::string get_xy_string(int x, int y) const;

    double get_xy_double(int x, int y) const;

    Cnumpy get_xy(int x, int y) const;


    friend std::ostream &operator<<(std::ostream &os, Cnumpy &obj);

    friend std::ostream &operator<<(std::ostream &os, Cnumpy &&obj);



    //Move to utils class

    int count(int column_index,Cnumpy value) const;

    Cnumpy get_min_value_in_column(int column_index) const;

    Cnumpy get_max_value_in_column(int column_index) const;

    Cnumpy get_unique_column_values(int column_index) const;

    Cnumpy hist(int column_index) const;


};


#endif
