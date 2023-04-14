#include <iostream>
#include "cnumpy/cnumpy.h"
#include "type.h"
#include "csv/csv.h"

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

    std::vector<int> x;
    x.push_back(-9);
    x.push_back(-9);
    x.push_back(-9);
    x.push_back(-9);
    x.push_back(-9);


    data.set_x(0,x);

    std::cout<<data;

   

    
    


   Cnumpy xd = CSV_reader::read_csv_file_as_cnumpy("C:\\Users\\Konrad\\Documents\\repo\\randomforrest\\randomforest\\RandomForest\\datasets\\iris\\data.csv");



   std::cout<<xd<<std::endl;

}