#include <iostream>
#include "cnumpy.h"
#include "type.h"
int main()
{
    std::cout << "Hello World!\n";
    std::vector<Type> typeCol = std::vector<Type>();
    typeCol.push_back(Type::integer_type);
    Cnumpy data = Cnumpy(2, 5, typeCol);
    std::vector<void *> dataCol = std::vector<void *>();
    dataCol.push_back((void *)123456789);
    dataCol.push_back((void*)2);
    dataCol.push_back((void*)3);
    dataCol.push_back((void*)4);
    dataCol.push_back((void*)5);


    std::vector<void*> dataCol2 = std::vector<void*>();
    dataCol2.push_back((void*)123456789);
    dataCol2.push_back((void*)2);
    dataCol2.push_back((void*)3);
    dataCol2.push_back((void*)4);
    dataCol2.push_back((void*)5);

    data.set_x(0, dataCol,Type::integer_type);
    data.set_x(1, dataCol2, Type::integer_type);

    std::cout << data;

}