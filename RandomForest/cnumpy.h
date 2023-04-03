#ifndef cnum_h
#define cnum_h
#include <vector>
#include "type.h"

class Cnumpy{

private:
	std::vector<std::vector<void*>> array_2d = std::vector<std::vector<void*>>();
	std::vector<Type>  type_column = std::vector<Type>();
	long x_dimension = 0;
	long y_dimension = 0;

	template<typename T>
	void check_size(std::vector<std::vector<T>>& vector_to_insert, long x, std::vector<T>& value);

	void check_size(std::vector<Type>& vector_to_insert, long x, Type& value);

	

public:
	Cnumpy(long x_dim, long y_dim, std::vector<Type> typeCol);
	void set_x(long x, std::vector<void*> columnValue,Type type_column);
	friend std::ostream& operator<<(std::ostream& os, const Cnumpy& obj);

	


};





#endif
