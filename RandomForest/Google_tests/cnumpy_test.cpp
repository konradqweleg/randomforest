//
// Created by konra on 22.04.2023.
//

#include "gtest/gtest.h"
#include "../cnumpy/cnumpy.h"
#include "../cnumpy/cnumpy.cpp"
#include <string>
#include <vector>

Cnumpy create_empty_cnumpy_3x3(){
    std::vector<Type> column_type = std::vector<Type>();
    column_type.push_back(Type::integer_type);
    column_type.push_back(Type::double_type);
    column_type.push_back(Type::string_type);


    std::vector<std::string> name_column = std::vector<std::string>();
    name_column.push_back("value_1");
    name_column.push_back("value_2");
    name_column.push_back("results");


    Cnumpy data = Cnumpy(3, 3, column_type, name_column);

    return data;
}

TEST(testCnumpy, create_empty_cnumpy_object)
{

    std::vector<Type> column_type = std::vector<Type>();
    column_type.push_back(Type::integer_type);
    column_type.push_back(Type::double_type);
    column_type.push_back(Type::string_type);


    std::vector<std::string> name_column = std::vector<std::string>();
    name_column.push_back("value_1");
    name_column.push_back("value_2");
    name_column.push_back("results");


    Cnumpy empty_created = Cnumpy(3, 3, column_type, name_column);

    EXPECT_EQ(3, empty_created.get_x_dimension());
    EXPECT_EQ(3, empty_created.get_y_dimension());

    std::vector<int> int_column = empty_created.get_column<int>(0);

    EXPECT_EQ(3,int_column.size());

    for(int value : int_column){
        EXPECT_EQ(0,value);
    }


    std::vector<double> double_column = empty_created.get_column<double>(1);

    EXPECT_EQ(3,double_column.size());

    for(double value : double_column){
        EXPECT_DOUBLE_EQ(0.0,value);
    }


    std::vector<std::string> string_column = empty_created.get_column_string(2);

    EXPECT_EQ(3,string_column.size());

    for(std::string value : string_column){
        EXPECT_EQ("",value);
    }






}