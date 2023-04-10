#include <iostream>
#include "cnumpy.h"
#include "type.h"
#include "csv.h"

#include <fstream>

int main()
{


    //Cnumpy test

    std::vector<Type> typeCol = std::vector<Type>();
    typeCol.push_back(Type::integer_type);
    typeCol.push_back(Type::double_type);
    typeCol.push_back(Type::integer_type);
    typeCol.push_back(Type::integer_type);
    typeCol.push_back(Type::integer_type);

    std::vector<std::string> nameC = std::vector<std::string>();
    nameC.push_back("name");
    nameC.push_back("xd");
    nameC.push_back("xd");
    nameC.push_back("xd2");
    nameC.push_back("xd3");

    Cnumpy data = Cnumpy(5,5,typeCol,nameC);

    data.set_xy(1,1,2.0);
    data.set_xy(2,0,1);
    data.set_xy(3,0,2);
    data.set_xy(4,3,3);

    std::cout<<data;

   

    
    


   Cnumpy xd = CSV_reader::read_csv_file_as_cnumpy("C:\\Users\\konra\\Documents\\PVM_Projekt\\randomforest\\x64\\Debug\\data.txt");



   std::cout<<xd<<std::endl;
    /*std::cout << "Hello World!\n";
    /*
   
    /*std::vector<Type> typeCol = std::vector<Type>();
    typeCol.push_back(Type::integer_type);
    typeCol.push_back(Type::integer_type);

    std::vector<std::string> nameC = std::vector<std::string>();
    nameC.push_back("name");
    nameC.push_back("xd");*/

   /* Cnumpy data = Cnumpy(2, 5, typeCol, nameC);
   // std::vector<void *> dataCol = std::vector<void *>();

   

    dataCol.push_back((void *)1234569);
    dataCol.push_back((void*)2);
    dataCol.push_back((void*)3);
    dataCol.push_back((void*)4);
    dataCol.push_back((void*)5);


    std::vector<int> dataCol2 = std::vector<int>();
    dataCol2.push_back(1234589);
    dataCol2.push_back(2);
    dataCol2.push_back(3);
    dataCol2.push_back(4);
    dataCol2.push_back(5);

    data.set_x(0, dataCol,Type::integer_type);
    data.set_x(1, dataCol2);

    data.set_xy(1, 0, -4);

    std::cout << data;

    */

//
}