#ifndef cnumpy_h
#define cnumpy_h

#include <vector>
#include "type.h"

/*Do zrobienia
 *  Dodanie operatorów (+=,-=,/=,mnozenie/)
 *  Dodanie const do metod ktore nie modyfikuja stanu
 *  Dodanieoperatora = tak aby mozna bylo przypisywac cnumpy 1x1,cnumpy 1xn i ,cnumpy nxn
 *  dodanie itertorow
 *  Dodanie testow brakuajcych
 *  wyjatkow kiedy argument poza  zakresem cnumpy
 *  refaktor kodu hist i pozostalych metod
 */



class Cnumpy {
//!! Add operator +=, add const,iteratory,set method allows set cnumpy,testy,wyjatki poza indexem dostep
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


    int how_many_column_about_type(Type type);

    int position_actual_column_in_type(Type type, int index_column) const;



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




   void throw_exception_when_cnumpy_has_more_then_one_element(Cnumpy data) const{
       if(data.get_y_dimension() > 1 || data.get_x_dimension() > 1){
           throw std::invalid_argument( "Only one element Cnumpy can be compare");
       }
   }

    void throw_exception_when_diffrent_type_value(Cnumpy data,Cnumpy data_2) const{
        Type first_type = data.get_type_columns()[0];
        Type second_type = data_2.get_type_columns()[0];

        if(first_type!=second_type){
            throw std::invalid_argument( "Diffrent value type");
        }
    }

    void check_is_correct_one_element_cnumpys(Cnumpy data,Cnumpy data_2) const{
        throw_exception_when_cnumpy_has_more_then_one_element(data);
        throw_exception_when_cnumpy_has_more_then_one_element(data_2);
        throw_exception_when_diffrent_type_value(data,data_2);

    }

public:


    static Cnumpy of(int value);

    static Cnumpy of(double value);

    static Cnumpy of(std::string value);


    Cnumpy get_xy(int x , int y);

    bool operator<( const Cnumpy & obj) const;

    bool operator<=(Cnumpy & obj);

    bool operator>(Cnumpy & obj);


    bool operator>=(Cnumpy & obj);



    bool operator==(Cnumpy & obj);

    bool operator!=(Cnumpy & obj);


    Cnumpy operator+(Cnumpy & obj);

    Cnumpy operator-(Cnumpy & obj);

    Cnumpy operator/(Cnumpy & obj);


    Cnumpy operator*(Cnumpy & obj);

    Cnumpy operator-();

    Cnumpy operator[](int index);


    Cnumpy(long x_dim, long y_dim, std::vector<Type> typeCol);

    Cnumpy(long x_dim, long y_dim, std::vector<Type> typeCol, std::vector<std::string> nameCol);

    std::vector<std::string> get_column_name();

    std::vector<Type> get_type_columns() const;

    int offset_calculate(Type type_column, int column_index);

    std::vector<std::string> get_column_string(int column_index);

    std::vector<double> get_column_double(int column);

    std::vector<int> get_column_int(int column);

    Cnumpy get_unique_column_values(int column_index);

    //int or sequence of str defines number of equal width bins in a range, default is 10
    Cnumpy hist(int column_index,double bins =1.0);


    int get_x_dimension();

    int get_y_dimension();

    Cnumpy get_min_value_in_column(int column_index);

    Cnumpy get_max_value_in_column(int column_index);

    void set_xy(int x, int y, int value);

    void set_xy(int x, int y, std::string value);

    void set_xy(int x, int y, double value);

    void set_xy(int x, int y, Cnumpy value);

    int get_xy_int(int x, int y) const;

    std::string get_xy_string(int x, int y) const;

    double get_xy_double(int x, int y) const;

    template<typename T>
    void set_column(long index_column, std::vector<T> column_values) {
        for (int i = 0; i < column_values.size(); ++i) {
            set_xy(index_column, i, column_values[i]);
        }
    };


    friend std::ostream &operator<<(std::ostream &os, Cnumpy &obj);


};


#endif
