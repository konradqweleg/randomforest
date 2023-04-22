#ifndef cnumpy_h
#define cnumpy_h
#include <vector>
#include "type.h"

class Cnumpy{

private:

    std::vector<std::string> string_store = std::vector<std::string>();
    std::vector<double> double_store = std::vector<double>();
    std::vector<int> int_store = std::vector<int>();

	std::vector<Type>  type_column = std::vector<Type>();
	std::vector<std::string> name_column = std::vector<std::string>();

	long x_dimension = 0;
	long y_dimension = 0;



	uint8_t width_printed_value_on_sysout = 20;


    int how_many_column_about_type(Type type);

    int position_actual_column_in_type(Type type,int index_column);
	

	

public:
	Cnumpy(long x_dim, long y_dim, std::vector<Type> typeCol);
	Cnumpy(long x_dim, long y_dim, std::vector<Type> typeCol,std::vector<std::string> nameCol);

    std::vector<std::string> get_column_name(){
        return name_column;
    }


    std::vector<std::string> get_column_string(int column){
        std::vector<std::string> result;
        int offset = (position_actual_column_in_type(Type::string_type, column)) * y_dimension;
        result= std::vector<std::string>(string_store.begin() + offset, string_store.begin() + offset+y_dimension);
        return  result;
    }
    std::vector<Type> get_type_column();

    template<typename T>
    std::vector<T> get_column(int column) {

        std::vector<T> result;
        if(get_type_column()[column] == Type::double_type) {

            int offset = (position_actual_column_in_type(Type::double_type, column)) * y_dimension;
            result =   std::vector<T>(double_store.begin() + offset, double_store.begin() + offset+y_dimension);
        }else if(get_type_column()[column] == Type::integer_type){
            int offset = (position_actual_column_in_type(Type::integer_type, column)) * y_dimension;
            result =   std::vector<T>(int_store.begin() + offset, int_store.begin() + offset+y_dimension);
        }

        return result;
    }





    int get_x_dimension(){
        return x_dimension;
    }


    int get_y_dimension(){
        return y_dimension;
    }

	void set_xy(int x, int y, int value);

    void set_xy(int x, int y, std::string value);

    void set_xy(int x, int y, double value);

    template<typename T>
    void set_x(long x, std::vector<T> column_values) {
        for (int i = 0; i < column_values.size(); ++i) {
                set_xy(x, i, column_values[i]);
        }
    };


	

	friend std::ostream& operator<<(std::ostream& os,  Cnumpy& obj);


};


#endif
