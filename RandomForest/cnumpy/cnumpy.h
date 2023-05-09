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



    template<typename T>
    Cnumpy create_cnumpy_with_one_column_from_raw_data(std::vector<T> raw_column_data, int x_dim, int y_dim, Type column_type, std::string column_name){
        std::vector<std::string> name_columns;
        name_columns.push_back(column_name);

        std::vector<Type> type_columns;
        type_columns.push_back(column_type);

        Cnumpy uniqued_cnumpy = Cnumpy(x_dim,y_dim,type_columns,name_columns);
        uniqued_cnumpy.set_column(0,raw_column_data);

        return uniqued_cnumpy;
    }


    template<typename T>
    static Cnumpy create_cnumpy_with_one_value(T raw_value, Type column_type, std::string column_name){
        std::vector<std::string> name_columns;
        name_columns.push_back(column_name);

        std::vector<Type> type_columns;
        type_columns.push_back(column_type);

        Cnumpy uniqued_cnumpy = Cnumpy(1,1,type_columns,name_columns);

        std::vector<T> data;
        data.push_back(raw_value);

        uniqued_cnumpy.set_column(0,data);

        return uniqued_cnumpy;
    }




   void throw_exception_when_cnumpy_has_more_then_one_element(Cnumpy data){
       if(data.get_y_dimension() > 1 || data.get_x_dimension() > 1){
           throw std::invalid_argument( "Only one element Cnumpy can be compare");
       }
   }

    void throw_exception_when_diffrent_type_value(Cnumpy data,Cnumpy data_2){
        Type first_type = data.get_type_columns()[0];
        Type second_type = data_2.get_type_columns()[0];

        if(first_type!=second_type){
            throw std::invalid_argument( "Diffrent value type");
        }
    }

    void check_is_correct_one_element_cnumpys(Cnumpy data,Cnumpy data_2){
        throw_exception_when_cnumpy_has_more_then_one_element(data);
        throw_exception_when_cnumpy_has_more_then_one_element(data_2);
        throw_exception_when_diffrent_type_value(data,data_2);

    }

public:


    static Cnumpy of(int value){
        return create_cnumpy_with_one_value(value, Type::integer_type, "*");
    }

    static Cnumpy of(double value){
        return create_cnumpy_with_one_value(value, Type::double_type, "*");
    }

    static Cnumpy of(std::string value){
        return create_cnumpy_with_one_value(value, Type::string_type, "*");
    }




    Cnumpy get_xy(int x , int y){
        Type col_type = get_type_columns()[x];

        if(col_type == Type::integer_type){
            int raw_value = get_xy_int(x,y);
            Cnumpy result = create_cnumpy_with_one_value(raw_value,col_type,"*");
            return result;
        }else if(col_type == Type::double_type){
            double raw_value = get_xy_double(x,y);
            Cnumpy result = create_cnumpy_with_one_value(raw_value,col_type,"*");
            return result;
        }else{
            std::string raw_value = get_xy_string(x,y);
            Cnumpy result = create_cnumpy_with_one_value(raw_value,col_type,"*");
            return result;
        }

    }

    bool operator<(Cnumpy & obj)
    {
        check_is_correct_one_element_cnumpys(obj,*this);
        Type type_value = obj.get_type_columns()[0];

        if(type_value == Type::integer_type){
            int my_value = get_xy_int(0,0);
            int other_value = obj.get_xy_int(0,0);
            return my_value < other_value;
        }else if(type_value == Type::double_type){
            double my_value = get_xy_double(0,0);
            double other_value = obj.get_xy_double(0,0);
            return my_value < other_value;
        }else{
            std::string my_value = get_xy_string(0,0);
            std::string other_value = obj.get_xy_string(0,0);
            return my_value < other_value;
        }

    }

    bool operator<=(Cnumpy & obj)
    {
        check_is_correct_one_element_cnumpys(obj,*this);
        Type type_value = obj.get_type_columns()[0];

        if(type_value == Type::integer_type){
            int my_value = get_xy_int(0,0);
            int other_value = obj.get_xy_int(0,0);
            return my_value <= other_value;
        }else if(type_value == Type::double_type){
            double my_value = get_xy_double(0,0);
            double other_value = obj.get_xy_double(0,0);
            return my_value <= other_value;
        }else{
            std::string my_value = get_xy_string(0,0);
            std::string other_value = obj.get_xy_string(0,0);
            return my_value <= other_value;
        }

    }

    bool operator>(Cnumpy & obj)
    {
        if(obj != (*this)) {
            return (!operator<(obj));
        }else{
            return false;
        }
    }

    bool operator>=(Cnumpy & obj)
    {
        check_is_correct_one_element_cnumpys(obj,*this);
        Type type_value = obj.get_type_columns()[0];

        if(type_value == Type::integer_type){
            int my_value = get_xy_int(0,0);
            int other_value = obj.get_xy_int(0,0);
            return my_value >= other_value;
        }else if(type_value == Type::double_type){
            double my_value = get_xy_double(0,0);
            double other_value = obj.get_xy_double(0,0);
            return my_value >= other_value;
        }else{
            std::string my_value = get_xy_string(0,0);
            std::string other_value = obj.get_xy_string(0,0);
            return my_value >= other_value;
        }
    }



    bool operator==(Cnumpy & obj)
    {
        check_is_correct_one_element_cnumpys(obj,*this);
        Type type_value = obj.get_type_columns()[0];

        if(type_value == Type::integer_type){
            int my_value = get_xy_int(0,0);
            int other_value = obj.get_xy_int(0,0);
            return my_value == other_value;
        }else if(type_value == Type::double_type){
            double my_value = get_xy_double(0,0);
            double other_value = obj.get_xy_double(0,0);

            return my_value == other_value;
        }else{
            std::string my_value = get_xy_string(0,0);
            std::string other_value = obj.get_xy_string(0,0);
            return my_value == other_value;
        }

    }

    bool operator!=(Cnumpy & obj)
    {
        return (!operator==(obj));
    }


    Cnumpy operator+(Cnumpy & obj)
    {
        check_is_correct_one_element_cnumpys(obj,*this);
        Type type_value = obj.get_type_columns()[0];

        if(type_value == Type::integer_type){
            int my_value = get_xy_int(0,0);
            int other_value = obj.get_xy_int(0,0);
            int result = my_value + other_value;

            Cnumpy result_as_cnumpy =  create_cnumpy_with_one_value(result,Type::integer_type,"+");
            return result_as_cnumpy;
        }else if(type_value == Type::double_type){
            double my_value = get_xy_double(0,0);
            double other_value = obj.get_xy_double(0,0);
            double result = my_value + other_value;

            Cnumpy result_as_cnumpy =  create_cnumpy_with_one_value(result,Type::double_type,"+");
            return result_as_cnumpy;
        }else{
            std::string my_value = get_xy_string(0,0);
            std::string other_value = obj.get_xy_string(0,0);
            std::string result = my_value + other_value;

            Cnumpy result_as_cnumpy =  create_cnumpy_with_one_value(result,Type::string_type,"+");
            return result_as_cnumpy;
        }

    }

    Cnumpy operator-(Cnumpy & obj)
    {
        check_is_correct_one_element_cnumpys(obj,*this);
        Type type_value = obj.get_type_columns()[0];

        if(type_value == Type::integer_type){
            int my_value = get_xy_int(0,0);
            int other_value = obj.get_xy_int(0,0);
            int result = my_value - other_value;

            Cnumpy result_as_cnumpy =  create_cnumpy_with_one_value(result,Type::integer_type,"+");
            return result_as_cnumpy;
        }else if(type_value == Type::double_type){
            double my_value = get_xy_double(0,0);
            double other_value = obj.get_xy_double(0,0);
            double result = my_value - other_value;

            Cnumpy result_as_cnumpy =  create_cnumpy_with_one_value(result,Type::double_type,"+");
            return result_as_cnumpy;
        }else{
            throw std::invalid_argument( "Operation minus on two string is banned");
        }

    }

    Cnumpy operator/(Cnumpy & obj)
    {
        check_is_correct_one_element_cnumpys(obj,*this);
        Type type_value = obj.get_type_columns()[0];

        if(type_value == Type::integer_type){
            int my_value = get_xy_int(0,0);
            int other_value = obj.get_xy_int(0,0);
            int result = my_value / other_value;

            Cnumpy result_as_cnumpy =  create_cnumpy_with_one_value(result,Type::integer_type,"+");
            return result_as_cnumpy;
        }else if(type_value == Type::double_type){
            double my_value = get_xy_double(0,0);
            double other_value = obj.get_xy_double(0,0);
            double result = my_value / other_value;

            Cnumpy result_as_cnumpy =  create_cnumpy_with_one_value(result,Type::double_type,"+");
            return result_as_cnumpy;
        }else{
            throw std::invalid_argument( "Operation / on two string is banned");
        }

    }


    Cnumpy operator*(Cnumpy & obj)
    {
        check_is_correct_one_element_cnumpys(obj,*this);
        Type type_value = obj.get_type_columns()[0];

        if(type_value == Type::integer_type){
            int my_value = get_xy_int(0,0);
            int other_value = obj.get_xy_int(0,0);
            int result = my_value * other_value;

            Cnumpy result_as_cnumpy =  create_cnumpy_with_one_value(result,Type::integer_type,"+");
            return result_as_cnumpy;
        }else if(type_value == Type::double_type){
            double my_value = get_xy_double(0,0);
            double other_value = obj.get_xy_double(0,0);
            double result = my_value * other_value;

            Cnumpy result_as_cnumpy =  create_cnumpy_with_one_value(result,Type::double_type,"+");
            return result_as_cnumpy;
        }else{
            throw std::invalid_argument( "Operation * on two string is banned");
        }

    }

    Cnumpy operator-(int)
    {
        check_is_correct_one_element_cnumpys(*this,*this);
        Type type_value = get_type_columns()[0];

        if(type_value == Type::integer_type){
            int my_value = get_xy_int(0,0);

            int result = -my_value ;

            Cnumpy result_as_cnumpy =  create_cnumpy_with_one_value(result,Type::integer_type,"+");
            return result_as_cnumpy;
        }else if(type_value == Type::double_type){
            double my_value = get_xy_double(0,0);

            double result = -my_value ;

            Cnumpy result_as_cnumpy =  create_cnumpy_with_one_value(result,Type::double_type,"+");
            return result_as_cnumpy;
        }else{
            throw std::invalid_argument( "Operation - on  string is banned");
        }

    }

    Cnumpy operator[](int index) {

        Type type_col = type_column[index];

        if(get_x_dimension() > 1){
            if(type_col == Type::integer_type){
                std::vector<int> column_with_integers = get_column_int(index);
                Cnumpy column_cnumpy= create_cnumpy_with_one_column_from_raw_data(column_with_integers,1,column_with_integers.size(),type_col,"*");
                return column_cnumpy;
            }else if(type_col == Type::double_type){
                std::vector<double> column_with_double = get_column_double(index);
                Cnumpy column_cnumpy= create_cnumpy_with_one_column_from_raw_data(column_with_double,1,column_with_double.size(),type_col,"*");
                return column_cnumpy;
            }else{
                std::vector<std::string> column_with_string = get_column_string(index);
                Cnumpy column_cnumpy= create_cnumpy_with_one_column_from_raw_data(column_with_string,1,column_with_string.size(),type_col,"*");
                return column_cnumpy;
            }

        }else{

            if(type_col == Type::integer_type){
                int value = get_xy_int(0,0);
                Cnumpy result_as_cnumpy =  create_cnumpy_with_one_value(value,Type::integer_type,"*");
                return result_as_cnumpy;
            }else if(type_col == Type::double_type){
                double value = get_xy_double(0,0);
                Cnumpy result_as_cnumpy =  create_cnumpy_with_one_value(value,Type::double_type,"*");
                return result_as_cnumpy;
            }else{
                std::string value = get_xy_string(0,0);
                Cnumpy result_as_cnumpy =  create_cnumpy_with_one_value(value,Type::string_type,"*");
                return result_as_cnumpy;
            }




        }



    }



    Cnumpy(long x_dim, long y_dim, std::vector<Type> typeCol);

    Cnumpy(long x_dim, long y_dim, std::vector<Type> typeCol, std::vector<std::string> nameCol);

    std::vector<std::string> get_column_name();

    std::vector<Type> get_type_columns();

    int offset_calculate(Type type_column, int column_index);

    std::vector<std::string> get_column_string(int column_index);

    std::vector<double> get_column_double(int column);

    std::vector<int> get_column_int(int column);

    Cnumpy get_unique_column_values(int column_index);

    //int or sequence of str defines number of equal width bins in a range, default is 10
    Cnumpy hist(int column_index,int bins);


    int get_x_dimension();

    int get_y_dimension();

    Cnumpy get_min_value_in_column(int column_index);

    Cnumpy get_max_value_in_column(int column_index);

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
