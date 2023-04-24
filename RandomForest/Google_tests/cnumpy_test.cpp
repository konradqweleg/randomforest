//
// Created by konra on 22.04.2023.
//

#include "gtest/gtest.h"
#include "../cnumpy/cnumpy.h"
#include "../cnumpy/cnumpy.cpp"
#include <string>
#include <vector>

Cnumpy create_empty_cnumpy_3x3() {
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

TEST(testCnumpy, create_empty_cnumpy_object) {

    Cnumpy empty_created = create_empty_cnumpy_3x3();

    EXPECT_EQ(3, empty_created.get_x_dimension());
    EXPECT_EQ(3, empty_created.get_y_dimension());

    std::vector<int> int_column = empty_created.get_column_int(0);

    EXPECT_EQ(3, int_column.size());

    for (int value: int_column) {
        EXPECT_EQ(0, value);
    }


    std::vector<double> double_column = empty_created.get_column_double(1);

    EXPECT_EQ(3, double_column.size());

    for (double value: double_column) {
        EXPECT_DOUBLE_EQ(0.0, value);
    }


    std::vector<std::string> string_column = empty_created.get_column_string(2);

    EXPECT_EQ(3, string_column.size());

    for (std::string value: string_column) {
        EXPECT_EQ("", value);
    }


}

TEST(testCnumpy, get_columns_type) {

    Cnumpy empty_created = create_empty_cnumpy_3x3();
    std::vector<Type> columns_type = empty_created.get_type_columns();

    EXPECT_EQ(Type::integer_type, columns_type[0]);
    EXPECT_EQ(Type::double_type, columns_type[1]);
    EXPECT_EQ(Type::string_type, columns_type[2]);


}

TEST(testCnumpy, get_columns_name) {

    Cnumpy empty_created = create_empty_cnumpy_3x3();
    std::vector<std::string> columns_name = empty_created.get_column_name();

    EXPECT_EQ("value_1", columns_name[0]);
    EXPECT_EQ("value_2", columns_name[1]);
    EXPECT_EQ("results", columns_name[2]);


}

TEST(testCnumpy, set_columns) {

    Cnumpy empty_created = create_empty_cnumpy_3x3();

    std::vector<int> int_column{10,20,30};
    std::vector<double> double_column{10.0,20.0,30.0};
    std::vector<std::string> string_column{"10","20","30"};

    empty_created.set_column(0,int_column);
    empty_created.set_column(1,double_column);
    empty_created.set_column(2,string_column);


    EXPECT_EQ(int_column, empty_created.get_column_int(0));
    EXPECT_EQ(double_column, empty_created.get_column_double(1));
    EXPECT_EQ(string_column, empty_created.get_column_string(2));


}
//ids
TEST(testCnumpy, set_xy) {

    Cnumpy empty_created = create_empty_cnumpy_3x3();

    empty_created.set_xy(0,0,10);
    empty_created.set_xy(1,0,10.0);
    empty_created.set_xy(2,0,"10");


    EXPECT_EQ(10, empty_created.get_xy_int(0,0));
    EXPECT_EQ(0, empty_created.get_xy_int(0,1));

    EXPECT_EQ(10.0, empty_created.get_xy_double(1,0));
    EXPECT_EQ(0.0, empty_created.get_xy_double(1,1));

    EXPECT_EQ("10", empty_created.get_xy_string(2,0));
    EXPECT_EQ("", empty_created.get_xy_string(2,1));

}