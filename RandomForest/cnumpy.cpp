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
	array_2d = std::vector<std::vector<void*>>(x_dim);

	for (int x = 0; x < x_dim; ++x) {
		name_column.push_back("_");
		array_2d[x] = std::vector<void*>(y_dim);
	}

}

void Cnumpy::set_x(long x, std::vector<void*> columnValue,Type type_col) {

	check_size(array_2d, x, columnValue);
	check_size(type_column, x, type_col);
}





void Cnumpy::check_size(std::vector<Type>& vector_to_insert, long x, Type& value) {
	
	if (vector_to_insert.size() <= x) {
		vector_to_insert.push_back(value);
	}
	else {
		vector_to_insert[x] = value;
	}
	
}

template<typename T>
void Cnumpy::check_size(std::vector<std::vector<T>>& vector_to_insert, long x, std::vector<T>& value) {

	if (vector_to_insert.size() <= x) {
		vector_to_insert.push_back(value);
	}
	else {
		vector_to_insert[x] = value;
	}

}




std::ostream& operator<<(std::ostream& os, const Cnumpy& obj) {

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
				
				os << std::left<< symbolVerticalBreak << std::setw(obj.setw) << ((int)obj.array_2d[x][y]) ;
			}
			
			
		}
		os << std::endl;
    }
	

   return os;
}



