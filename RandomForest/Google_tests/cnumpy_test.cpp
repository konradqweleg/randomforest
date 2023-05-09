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


Cnumpy create_fill_cnumpy_3x3_increased_value_int_double_string(){
    Cnumpy data = create_empty_cnumpy_3x3();

    std::vector<int> int_column{10,20,30};
    std::vector<double> double_column{10.0,20.0,30.0};
    std::vector<std::string> string_column{"10","20","30"};

    data.set_column(0,int_column);
    data.set_column(1,double_column);
    data.set_column(2,string_column);
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

TEST(testCnumpy,get_unique_column_value){
    Cnumpy data = create_empty_cnumpy_3x3();

    std::vector<int> int_column{10,10,30};
    std::vector<double> double_column{10.0,30.0,10.0};
    std::vector<std::string> string_column{"10","20","30"};

    data.set_column(0,int_column);
    data.set_column(1,double_column);
    data.set_column(2,string_column);

    Cnumpy unique_int_column_values = data.get_unique_column_values(0);
    EXPECT_EQ(2,unique_int_column_values.get_y_dimension());
    EXPECT_EQ(10,unique_int_column_values.get_xy_int(0,0));
    EXPECT_EQ(30,unique_int_column_values.get_xy_int(0,1));

    Cnumpy unique_double_column_values = data.get_unique_column_values(1);
    EXPECT_EQ(2,unique_double_column_values.get_y_dimension());
    ASSERT_DOUBLE_EQ(10.0,unique_double_column_values.get_xy_double(0,0));
    ASSERT_DOUBLE_EQ(30.0,unique_double_column_values.get_xy_double(0,1));

    Cnumpy unique_string_column_values = data.get_unique_column_values(2);
    EXPECT_EQ(3,unique_string_column_values.get_y_dimension());
    EXPECT_EQ("10",unique_string_column_values.get_xy_string(0,0));
    EXPECT_EQ("20",unique_string_column_values.get_xy_string(0,1));
    EXPECT_EQ("30",unique_string_column_values.get_xy_string(0,2));


}

TEST(testCnumpy,get_min_value_in_column){
    Cnumpy data = create_empty_cnumpy_3x3();

    std::vector<int> int_column{30,10,0};
    std::vector<double> double_column{20.0,10.0,30.0};
    std::vector<std::string> string_column{"aa","cc","xx"};

    data.set_column(0,int_column);
    data.set_column(1,double_column);
    data.set_column(2,string_column);

    Cnumpy min_int_value = data.get_min_value_in_column(0);
    Cnumpy min_double_value = data.get_min_value_in_column(1);
    Cnumpy min_string_value = data.get_min_value_in_column(2);


    EXPECT_EQ(0,min_int_value.get_xy_int(0,0));
    ASSERT_DOUBLE_EQ(10.0,min_double_value.get_xy_double(0,0));
    EXPECT_EQ("aa",min_string_value.get_xy_string(0,0));

}

TEST(testCnumpy,get_max_value_in_column){
    Cnumpy data = create_empty_cnumpy_3x3();

    std::vector<int> int_column{30,10,0};
    std::vector<double> double_column{20.0,10.0,30.0};
    std::vector<std::string> string_column{"aa","cc","xx"};

    data.set_column(0,int_column);
    data.set_column(1,double_column);
    data.set_column(2,string_column);

    Cnumpy max_int_value = data.get_max_value_in_column(0);
    Cnumpy max_double_value = data.get_max_value_in_column(1);
    Cnumpy max_string_value = data.get_max_value_in_column(2);


    EXPECT_EQ(30,max_int_value.get_xy_int(0,0));
    ASSERT_DOUBLE_EQ(30.0,max_double_value.get_xy_double(0,0));
    EXPECT_EQ("xx",max_string_value.get_xy_string(0,0));

}



TEST(testCnumpy,get_xy_cnumpy){
    Cnumpy data = create_fill_cnumpy_3x3_increased_value_int_double_string();

    Cnumpy value_int_0 = data.get_xy(0,0);
    Cnumpy value_int_1= data.get_xy(0,1);
    Cnumpy value_int_2 = data.get_xy(0,2);

    EXPECT_EQ(10,value_int_0.get_xy_int(0,0));
    EXPECT_EQ(20,value_int_1.get_xy_int(0,0));
    EXPECT_EQ(30,value_int_2.get_xy_int(0,0));



    Cnumpy value_double_0 = data.get_xy(1,0);
    Cnumpy value_double_1= data.get_xy(1,1);
    Cnumpy value_double_2 = data.get_xy(1,2);

    ASSERT_DOUBLE_EQ(10.0,value_double_0.get_xy_double(0,0));
    ASSERT_DOUBLE_EQ(20.0,value_double_1.get_xy_double(0,0));
    ASSERT_DOUBLE_EQ(30.0,value_double_2.get_xy_double(0,0));




    Cnumpy value_string_0 = data.get_xy(2,0);
    Cnumpy value_string_1 = data.get_xy(2,1);
    Cnumpy value_string_2 = data.get_xy(2,2);


    EXPECT_EQ("10",value_string_0.get_xy_string(0,0));
    EXPECT_EQ("20",value_string_1.get_xy_string(0,0));
    EXPECT_EQ("30",value_string_2.get_xy_string(0,0));

}

TEST(testCnumpy,of){
    Cnumpy int_value_cnumpy = Cnumpy::of(5);
    EXPECT_EQ(5,int_value_cnumpy.get_xy_int(0,0));

    Cnumpy double_value_cnumpy = Cnumpy::of(15.0);
    ASSERT_DOUBLE_EQ(15.0,double_value_cnumpy.get_xy_double(0,0));

    Cnumpy string_value_cnumpy = Cnumpy::of("text");
    EXPECT_EQ("text",string_value_cnumpy.get_xy_string(0,0));
}



TEST(testCnumpy,operator_lower){
    Cnumpy int_value_5_cnumpy = Cnumpy::of(5);
    Cnumpy int_value_10_cnumpy = Cnumpy::of(10);

    Cnumpy double_value_5_cnumpy = Cnumpy::of(5.0);
    Cnumpy double_value_10_cnumpy = Cnumpy::of(10.0);

    Cnumpy string_value_aa_cnumpy = Cnumpy::of("aa");
    Cnumpy string_value_bb_cnumpy = Cnumpy::of("bb");


    EXPECT_TRUE(int_value_5_cnumpy<int_value_10_cnumpy);
    EXPECT_TRUE(double_value_5_cnumpy<double_value_10_cnumpy);
    EXPECT_TRUE(string_value_aa_cnumpy<string_value_bb_cnumpy);

    EXPECT_FALSE(int_value_10_cnumpy<int_value_5_cnumpy);
    EXPECT_FALSE(double_value_10_cnumpy<double_value_5_cnumpy);
    EXPECT_FALSE(string_value_bb_cnumpy<string_value_aa_cnumpy);

    EXPECT_FALSE(int_value_10_cnumpy<int_value_10_cnumpy);
    EXPECT_FALSE(double_value_10_cnumpy<double_value_10_cnumpy);
    EXPECT_FALSE(string_value_bb_cnumpy<string_value_bb_cnumpy);


}

TEST(testCnumpy,operator_lower_or_equal){
    Cnumpy int_value_5_cnumpy = Cnumpy::of(5);
    Cnumpy int_value_10_cnumpy = Cnumpy::of(10);

    Cnumpy double_value_5_cnumpy = Cnumpy::of(5.0);
    Cnumpy double_value_10_cnumpy = Cnumpy::of(10.0);

    Cnumpy string_value_aa_cnumpy = Cnumpy::of("aa");
    Cnumpy string_value_bb_cnumpy = Cnumpy::of("bb");


    EXPECT_TRUE(int_value_5_cnumpy<=int_value_10_cnumpy);
    EXPECT_TRUE(double_value_5_cnumpy<=double_value_10_cnumpy);
    EXPECT_TRUE(string_value_aa_cnumpy<=string_value_bb_cnumpy);

    EXPECT_FALSE(int_value_10_cnumpy<=int_value_5_cnumpy);
    EXPECT_FALSE(double_value_10_cnumpy<=double_value_5_cnumpy);
    EXPECT_FALSE(string_value_bb_cnumpy<=string_value_aa_cnumpy);

    EXPECT_TRUE(int_value_10_cnumpy<=int_value_10_cnumpy);
    EXPECT_TRUE(double_value_10_cnumpy<=double_value_10_cnumpy);
    EXPECT_TRUE(string_value_bb_cnumpy<=string_value_bb_cnumpy);


}

TEST(testCnumpy,operator_greater){
    Cnumpy int_value_5_cnumpy = Cnumpy::of(5);
    Cnumpy int_value_10_cnumpy = Cnumpy::of(10);

    Cnumpy double_value_5_cnumpy = Cnumpy::of(5.0);
    Cnumpy double_value_10_cnumpy = Cnumpy::of(10.0);

    Cnumpy string_value_aa_cnumpy = Cnumpy::of("aa");
    Cnumpy string_value_bb_cnumpy = Cnumpy::of("bb");


    EXPECT_FALSE(int_value_5_cnumpy>int_value_10_cnumpy);
    EXPECT_FALSE(double_value_5_cnumpy>double_value_10_cnumpy);
    EXPECT_FALSE(string_value_aa_cnumpy>string_value_bb_cnumpy);

    EXPECT_TRUE(int_value_10_cnumpy>int_value_5_cnumpy);
    EXPECT_TRUE(double_value_10_cnumpy>double_value_5_cnumpy);
    EXPECT_TRUE(string_value_bb_cnumpy>string_value_aa_cnumpy);

    EXPECT_FALSE(int_value_10_cnumpy>int_value_10_cnumpy);
    EXPECT_FALSE(double_value_10_cnumpy>double_value_10_cnumpy);
    EXPECT_FALSE(string_value_bb_cnumpy>string_value_bb_cnumpy);


}

TEST(testCnumpy,operator_greater_or_equal){
    Cnumpy int_value_5_cnumpy = Cnumpy::of(5);
    Cnumpy int_value_10_cnumpy = Cnumpy::of(10);

    Cnumpy double_value_5_cnumpy = Cnumpy::of(5.0);
    Cnumpy double_value_10_cnumpy = Cnumpy::of(10.0);

    Cnumpy string_value_aa_cnumpy = Cnumpy::of("aa");
    Cnumpy string_value_bb_cnumpy = Cnumpy::of("bb");


    EXPECT_FALSE(int_value_5_cnumpy>=int_value_10_cnumpy);
    EXPECT_FALSE(double_value_5_cnumpy>=double_value_10_cnumpy);
    EXPECT_FALSE(string_value_aa_cnumpy>=string_value_bb_cnumpy);

    EXPECT_TRUE(int_value_10_cnumpy>=int_value_5_cnumpy);
    EXPECT_TRUE(double_value_10_cnumpy>=double_value_5_cnumpy);
    EXPECT_TRUE(string_value_bb_cnumpy>=string_value_aa_cnumpy);

    EXPECT_TRUE(int_value_10_cnumpy>=int_value_10_cnumpy);
    EXPECT_TRUE(double_value_10_cnumpy>=double_value_10_cnumpy);
    EXPECT_TRUE(string_value_bb_cnumpy>=string_value_bb_cnumpy);


}


TEST(testCnumpy,operator_equal){
    Cnumpy int_value_5_cnumpy = Cnumpy::of(5);
    Cnumpy int_value_10_cnumpy = Cnumpy::of(10);

    Cnumpy double_value_5_cnumpy = Cnumpy::of(5.0);
    Cnumpy double_value_10_cnumpy = Cnumpy::of(10.0);

    Cnumpy string_value_aa_cnumpy = Cnumpy::of("aa");
    Cnumpy string_value_bb_cnumpy = Cnumpy::of("bb");


    EXPECT_FALSE(int_value_5_cnumpy==int_value_10_cnumpy);
    EXPECT_FALSE(double_value_5_cnumpy==double_value_10_cnumpy);
    EXPECT_FALSE(string_value_aa_cnumpy==string_value_bb_cnumpy);

    EXPECT_TRUE(int_value_10_cnumpy==int_value_10_cnumpy);
    EXPECT_TRUE(double_value_10_cnumpy==double_value_10_cnumpy);
    EXPECT_TRUE(string_value_bb_cnumpy==string_value_bb_cnumpy);


}

TEST(testCnumpy,operator_not_equal){
    Cnumpy int_value_5_cnumpy = Cnumpy::of(5);
    Cnumpy int_value_10_cnumpy = Cnumpy::of(10);

    Cnumpy double_value_5_cnumpy = Cnumpy::of(5.0);
    Cnumpy double_value_10_cnumpy = Cnumpy::of(10.0);

    Cnumpy string_value_aa_cnumpy = Cnumpy::of("aa");
    Cnumpy string_value_bb_cnumpy = Cnumpy::of("bb");


    EXPECT_TRUE(int_value_5_cnumpy!=int_value_10_cnumpy);
    EXPECT_TRUE(double_value_5_cnumpy!=double_value_10_cnumpy);
    EXPECT_TRUE(string_value_aa_cnumpy!=string_value_bb_cnumpy);

    EXPECT_FALSE(int_value_10_cnumpy!=int_value_10_cnumpy);
    EXPECT_FALSE(double_value_10_cnumpy!=double_value_10_cnumpy);
    EXPECT_FALSE(string_value_bb_cnumpy!=string_value_bb_cnumpy);


}


TEST(testCnumpy,operator_add){
    Cnumpy int_value_5_cnumpy = Cnumpy::of(5);
    Cnumpy int_value_10_cnumpy = Cnumpy::of(10);
    Cnumpy result_add_int = int_value_5_cnumpy + int_value_10_cnumpy;

    Cnumpy double_value_5_cnumpy = Cnumpy::of(5.0);
    Cnumpy double_value_10_cnumpy = Cnumpy::of(10.0);
    Cnumpy result_add_double = double_value_5_cnumpy + double_value_10_cnumpy;

    Cnumpy string_value_aa_cnumpy = Cnumpy::of("aa");
    Cnumpy string_value_bb_cnumpy = Cnumpy::of("bb");
    Cnumpy result_add_string = string_value_aa_cnumpy + string_value_bb_cnumpy;


    EXPECT_EQ(15, result_add_int.get_xy_int(0, 0));
    EXPECT_DOUBLE_EQ(15.0,result_add_double.get_xy_double(0,0));
    EXPECT_EQ("aabb", result_add_string.get_xy_string(0, 0));


}

TEST(testCnumpy,operator_subtraction){
    Cnumpy int_value_5_cnumpy = Cnumpy::of(5);
    Cnumpy int_value_10_cnumpy = Cnumpy::of(10);
    Cnumpy result_substract_int = int_value_5_cnumpy - int_value_10_cnumpy;

    Cnumpy double_value_5_cnumpy = Cnumpy::of(5.0);
    Cnumpy double_value_10_cnumpy = Cnumpy::of(10.0);
    Cnumpy result_substract_double = double_value_10_cnumpy - double_value_5_cnumpy;

    EXPECT_EQ(-5, result_substract_int.get_xy_int(0, 0));
    EXPECT_DOUBLE_EQ(5.0, result_substract_double.get_xy_double(0, 0));



}