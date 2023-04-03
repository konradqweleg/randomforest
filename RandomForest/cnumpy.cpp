#include "cnumpy.h"
#include <vector>
#include "type.h"


Cnumpy::Cnumpy(long x_dim, long y_dim, std::vector<Type> type_col) {
	x_dimension = x_dim;
	y_dimension = y_dim;
	type_column = type_col;
	array_2d = std::vector<std::vector<void*>>(x_dim);

	for (int x = 0; x < x_dim; ++x) {
		array_2d[x] = std::vector<void*>(y_dim);
	}
}

void Cnumpy::set_x(long x, std::vector<void*> columnValue,Type type_col) {
	array_2d[x] = columnValue;
	type_column[x] = type_col;

}


std::ostream& operator<<(std::ostream& os, const Cnumpy& obj) {
	
	for (int x = 0; x < obj.x_dimension; x++) {
		for (int y = 0; y < obj.y_dimension; y++) {
			
			if (obj.type_column[x] == Type::integer_type) {
				os << ((int)obj.array_2d[x][y]) << " ";
			}
			os << std::endl;

		}
    }
	

   return os;
}


/*
	std::vector<void*> array_2d = std::vector<void*>();
	std::vector<Type>  type_column = std::vector<Type>();
	long x_dimension = 0;
	long y_dimension = 0;
*/