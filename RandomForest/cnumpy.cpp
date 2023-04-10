#include "cnumpy.h"
#include <vector>
#include "type.h"
#include <iomanip>



Cnumpy::Cnumpy(long x_dim, long y_dim, std::vector<Type> type_col,std::vector<std::string> nameCol):Cnumpy(x_dim, y_dim, type_col) {
	
	name_column = nameCol;
	//;
}


Cnumpy::Cnumpy(long x_dim, long y_dim, std::vector<Type> type_col) {
	x_dimension = x_dim;
	y_dimension = y_dim;
	type_column = type_col;

    int how_many_int_type_column = how_many_column_about_type(Type::integer_type);
    for(int i =0 ; i<how_many_int_type_column;++i){
        for(int x = 0; x<y_dim;++x){
            int_store.push_back(0);
        }
    }

    int how_many_double_type_column = how_many_column_about_type(Type::double_type);
    for(int i =0 ; i<how_many_double_type_column;++i){
        for(int x = 0; x<y_dim;++x){
            double_store.push_back(0.0);
        }
    }

    int how_many_string_type_column = how_many_column_about_type(Type::string_type);
    for(int i =0 ; i<how_many_string_type_column;++i){
        for(int x = 0; x<y_dim;++x){
            string_store.push_back("");
        }
    }


}

void Cnumpy::set_x(long x, std::vector<void*> columnValue,Type type_col) {

	//check_size(array_2d, x, columnValue);
	//check_size(type_column, x, type_col);
}





void Cnumpy::check_size(std::vector<Type>& vector_to_insert, long x, Type& value) {
	
	/*if (vector_to_insert.size() <= x) {
		vector_to_insert.push_back(value);
	}
	else {
		vector_to_insert[x] = value;
	}*/
	
}

template<typename T>
void Cnumpy::check_size(std::vector<std::vector<T>>& vector_to_insert, long x, std::vector<T>& value) {

	/*if (vector_to_insert.size() <= x) {
		vector_to_insert.push_back(value);
	}
	else {
		vector_to_insert[x] = value;
	}
*/
}







std::ostream& operator<<(std::ostream& os,  Cnumpy& obj) {

	static const char* Type_as_text[] = { "Integer", "Double", "String" };
	char symbolVerticalBreak = '|';
	char symbolHorizontalBreak = '-';

	os << std::right << std::setw(obj.setw) << "";
	for (std::string name : obj.name_column) {
		os << std::left << symbolVerticalBreak << std::setw(obj.setw) << name << "";
	}
	os << std::endl;
	
	os << std::right << std::setw(obj.setw) << "";
	for (Type type : obj.type_column) {
		os << std::left <<symbolVerticalBreak<< std::setw(obj.setw) << Type_as_text[type] << "";
	}

	os << std::endl;
	os << std::right << std::setw(obj.setw) << "";
	for (int i = 0; i < obj.type_column.size();++i) {
		os << symbolVerticalBreak << std::left << std::setw(obj.setw) << i << "";
	}
	os << std::endl;
	
	for (int i = 0; i < obj.setw +(obj.x_dimension* obj.setw); ++i) {
		os << symbolHorizontalBreak;
	}

	os << std::endl;

	for (int y = 0; y < obj.y_dimension; y++) {
		os << std::left << std::setw(obj.setw) << y;
		for (int x = 0; x < obj.x_dimension; x++) {
			
			if (obj.type_column[x] == Type::integer_type) {

                int position = obj.position_actual_column_in_type(Type::integer_type,x) * obj.y_dimension;
//obj.int_store[position+y]<<":"<<
                os << std::left << symbolVerticalBreak << std::setw(obj.setw) << obj.int_store[position+y];

			}else if(obj.type_column[x] ==Type::double_type){
                int position = obj.position_actual_column_in_type(Type::double_type,x) * obj.y_dimension;
                os << std::left << symbolVerticalBreak << std::setw(obj.setw) << obj.double_store[position+y];
            }else{
                int position = obj.position_actual_column_in_type(Type::string_type,x) * obj.y_dimension;
                os << std::left << symbolVerticalBreak << std::setw(obj.setw) << obj.string_store[position+y];
                //  os << std::left << symbolVerticalBreak << std::setw(obj.setw) << 0.0;
            }
			
			
		}
		os << std::endl;
    }
	

   return os;
}



