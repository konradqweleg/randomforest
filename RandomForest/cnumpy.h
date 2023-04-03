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

public:
	Cnumpy(long x_dim, long y_dim, std::vector<Type> typeCol);
	void set_x(long x, std::vector<void*> columnValue,Type type_column);
	friend std::ostream& operator<<(std::ostream& os, const Cnumpy& obj);

	


};





#endif
