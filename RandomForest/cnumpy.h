#ifndef cnum_h
#define cnum_h
#include <vector>
#include "type.h"

class Cnumpy{

private:
	

	

	std::vector<std::vector<void*>> array_2d = std::vector<std::vector<void*>>();
	std::vector<Type>  type_column = std::vector<Type>();
	std::vector<std::string> name_column = std::vector<std::string>();
	long x_dimension = 0;
	long y_dimension = 0;

	template<typename T>
	void check_size(std::vector<std::vector<T>>& vector_to_insert, long x, std::vector<T>& value);

	void check_size(std::vector<Type>& vector_to_insert, long x, Type& value);

	uint8_t setw = 20;
	

	

public:
	Cnumpy(long x_dim, long y_dim, std::vector<Type> typeCol);
	Cnumpy(long x_dim, long y_dim, std::vector<Type> typeCol,std::vector<std::string> nameCol);

	void set_x(long x, std::vector<void*> columnValue,Type type_column);

    std::vector<Type> get_type_column(){
        return type_column;
    }

	template<typename T>
	void set_xy(int x, int y, T value) {
		array_2d[x][y] =reinterpret_cast<T *> ( &value);
        std::cout<<":D =>"<<reinterpret_cast<T *> ( &value);
	};

;

	template<typename T>
	void set_x(long x, std::vector<T> columnValue) {

		std::vector<void*> emptyTable = std::vector<void*>();
		for (T value : columnValue) {
			emptyTable.push_back((void*)value);
		}

		Type typeC;
		if (std::is_same<T, int>::value) {
			typeC = Type::integer_type;
		}
		else if (std::is_same<T, int>::value) {
			typeC = Type::double_type;
		}
		else {
			typeC = Type::string_type;
		}


		check_size(array_2d, x, emptyTable);
		check_size(type_column, x, typeC);
	};
	

	friend std::ostream& operator<<(std::ostream& os, const Cnumpy& obj);

	


};





#endif
