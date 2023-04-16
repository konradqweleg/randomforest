#include <iostream>
#include "cnumpy/cnumpy.h"
#include "type.h"
#include "csv/csv.h"

#include <fstream>
#include "decision_tree/decision_tree.h"

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

   // std::cout<<data;

   

    
    


   Cnumpy xd = CSV_reader::read_csv_file_as_cnumpy("C:\\Users\\Konrad\\Documents\\repo\\randomforrest\\randomforest\\RandomForest\\datasets\\tests\\data.csv");



   std::cout<<xd<<std::endl;


   // decision_tree::quant_data(xd,0.10,"xd");


    std::vector<int> result_column = xd.get_column<int>(2);


    for(int a : result_column){
        std::cout<<a<<std::endl;
    }

    std::cout<<"Entropia rezultat : "<<decision_tree::entropy_result(result_column)<<std::endl;

    std::map<int,double> entropy = decision_tree::entropy_for_column(xd.get_column<int>(0),result_column);


    for(std::map<int,double>::iterator iter = entropy.begin(); iter != entropy.end(); ++iter)
    {
        int k =  iter->first;

        double v = iter->second;
        std::cout<<"Key = "<<k<<" Value = "<<v<<std::endl;
    }

    std::cout<<"Gotowe";



}