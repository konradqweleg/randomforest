//
// Created by konra on 22.04.2023.
//

#include "gtest/gtest.h"
#include "../cnumpy/cnumpy.h"
#include "../cnumpy/cnumpy.cpp"
#include <string>
#include <vector>
#include "exception_assert_for_gtest.h"
#include "../cnumpy/Exception_Cnumpy_Message.h"
#include "../cnumpy/Exception_Cnumpy_Message.cpp"

Cnumpy create_empty_cnumpy_3x3_int_double_string() {
    std::vector<Type> column_type = std::vector<Type>();
    column_type.push_back(Type::integer_type);
    column_type.push_back(Type::double_type);
    column_type.push_back(Type::string_type);


    std::vector<std::string> name_column = std::vector<std::string>();
    name_column.emplace_back("value_1");
    name_column.emplace_back("value_2");
    name_column.emplace_back("results");


    Cnumpy data = Cnumpy(3, 3, column_type, name_column);

    return data;
}


Cnumpy create_fill_cnumpy_3x3_increased_value_int_double_string() {
    Cnumpy data = create_empty_cnumpy_3x3_int_double_string();

    std::vector<int> int_column{10, 20, 30};
    std::vector<double> double_column{10.0, 20.0, 30.0};
    std::vector<std::string> string_column{"10", "20", "30"};

    data.set_column(0, int_column);
    data.set_column(1, double_column);
    data.set_column(2, string_column);
    return data;
}

TEST(testCnumpy, create_empty_cnumpy_check_dimension) {

    //when
    Cnumpy empty_created_3x3 = create_empty_cnumpy_3x3_int_double_string();


    //then
    EXPECT_EQ(3, empty_created_3x3.get_x_dimension());
    EXPECT_EQ(3, empty_created_3x3.get_y_dimension());

    std::vector<int> int_column = empty_created_3x3.get_column_int(0);
    EXPECT_EQ(3, int_column.size());

    std::vector<double> double_column = empty_created_3x3.get_column_double(1);
    EXPECT_EQ(3, double_column.size());

    std::vector<std::string> string_column = empty_created_3x3.get_column_string(2);
    EXPECT_EQ(3, string_column.size());


}

TEST(testCnumpy, create_cnumpy_with_unallowed_dimension) {

    //when
    //then
    ASSERT_EXCEPTION({ Cnumpy both_dimension_negative(-1, -1, std::vector<Type>()); }, std::invalid_argument,
                     Exception_Cnumpy_Message::BOTH_DIMENSION_MUST_BE_ABOVE_ZERO);
    ASSERT_EXCEPTION({ Cnumpy left_negative(-1, 1, std::vector<Type>()); }, std::invalid_argument,
                     Exception_Cnumpy_Message::BOTH_DIMENSION_MUST_BE_ABOVE_ZERO);
    ASSERT_EXCEPTION({ Cnumpy right_negative(1, -1, std::vector<Type>()); }, std::invalid_argument,
                     Exception_Cnumpy_Message::BOTH_DIMENSION_MUST_BE_ABOVE_ZERO);
    ASSERT_EXCEPTION({ Cnumpy both_zero(0, 0, std::vector<Type>()); }, std::invalid_argument,
                     Exception_Cnumpy_Message::BOTH_DIMENSION_MUST_BE_ABOVE_ZERO);
    ASSERT_EXCEPTION({ Cnumpy left_zero(0, 1, std::vector<Type>()); }, std::invalid_argument,
                     Exception_Cnumpy_Message::BOTH_DIMENSION_MUST_BE_ABOVE_ZERO);
    ASSERT_EXCEPTION({ Cnumpy right_zero(1, 0, std::vector<Type>()); }, std::invalid_argument,
                     Exception_Cnumpy_Message::BOTH_DIMENSION_MUST_BE_ABOVE_ZERO);
}

TEST(testCnumpy, create_empty_cnumpy_check_default_values) {

    //when
    Cnumpy empty_created = create_empty_cnumpy_3x3_int_double_string();

    //then
    std::vector<int> fresh_integer_column = empty_created.get_column_int(0);
    EXPECT_EQ(3, fresh_integer_column.size());
    for (int value: fresh_integer_column) {
        EXPECT_EQ(0, value);
    }

    std::vector<double> fresh_double_column = empty_created.get_column_double(1);
    EXPECT_EQ(3, fresh_double_column.size());
    for (double value: fresh_double_column) {
        EXPECT_DOUBLE_EQ(0.0, value);
    }

    std::vector<std::string> fresh_string_column = empty_created.get_column_string(2);
    EXPECT_EQ(3, fresh_string_column.size());
    for (const std::string &value: fresh_string_column) {
        EXPECT_EQ("", value);
    }


}

TEST(testCnumpy, get_columns_type) {

    //when
    Cnumpy empty_created = create_empty_cnumpy_3x3_int_double_string();
    std::vector<Type> columns_type = empty_created.get_type_columns();

    //then
    EXPECT_EQ(3, columns_type.size());
    EXPECT_EQ(Type::integer_type, columns_type[0]);
    EXPECT_EQ(Type::double_type, columns_type[1]);
    EXPECT_EQ(Type::string_type, columns_type[2]);


}

TEST(testCnumpy, get_columns_name) {

    //when
    Cnumpy empty_created = create_empty_cnumpy_3x3_int_double_string();
    std::vector<std::string> columns_name = empty_created.get_column_name();

    //then
    EXPECT_EQ(3, columns_name.size());
    EXPECT_EQ("value_1", columns_name[0]);
    EXPECT_EQ("value_2", columns_name[1]);
    EXPECT_EQ("results", columns_name[2]);


}

TEST(testCnumpy, set_columns) {

    //given
    Cnumpy empty_created = create_empty_cnumpy_3x3_int_double_string();

    std::vector<int> int_column{10, 20, 30};
    std::vector<double> double_column{10.0, 20.0, 30.0};
    std::vector<std::string> string_column{"10", "20", "30"};

    //when
    empty_created.set_column(0, int_column);
    empty_created.set_column(1, double_column);
    empty_created.set_column(2, string_column);


    //then
    EXPECT_EQ(int_column, empty_created.get_column_int(0));
    EXPECT_EQ(double_column, empty_created.get_column_double(1));
    EXPECT_EQ(string_column, empty_created.get_column_string(2));
    EXPECT_EQ(3, empty_created.get_y_dimension());
    EXPECT_EQ(3, empty_created.get_x_dimension());


}

TEST(testCnumpy, set_columns_use_unallowed_index) {
    //given
    Cnumpy empty_created = create_empty_cnumpy_3x3_int_double_string();
    std::vector<int> int_column{10, 20, 30};

    //then
    ASSERT_EXCEPTION({ empty_created.set_column(-1, int_column); }, std::invalid_argument,
                     Exception_Cnumpy_Message::ACCESS_INDEX_MUST_BE_GREATER_OR_EQUAL_ZERO);
    ASSERT_EXCEPTION({ empty_created.set_column(5, int_column); }, std::invalid_argument,
                     Exception_Cnumpy_Message::INDEXES_MUST_BE_SMALLER_THAN_DIMENSION_OF_CNUMPY);
    ASSERT_EXCEPTION({ empty_created.set_column(2, int_column); }, std::invalid_argument,
                     Exception_Cnumpy_Message::VALUE_TYPE_DO_NOT_MATCH);
}

TEST(testCnumpy, set_xy) {

    //given
    Cnumpy empty_created = create_empty_cnumpy_3x3_int_double_string();

    //when
    empty_created.set_xy(0, 0, 10);
    empty_created.set_xy(1, 0, 10.0);
    empty_created.set_xy(2, 0, "10");


    //then
    EXPECT_EQ(10, empty_created.get_xy_int(0, 0));
    EXPECT_EQ(0, empty_created.get_xy_int(0, 1));

    EXPECT_EQ(10.0, empty_created.get_xy_double(1, 0));
    EXPECT_EQ(0.0, empty_created.get_xy_double(1, 1));

    EXPECT_EQ("10", empty_created.get_xy_string(2, 0));
    EXPECT_EQ("", empty_created.get_xy_string(2, 1));


}

TEST(testCnumpy, set_xy_unallowed_index) {

    //given
    Cnumpy empty_created = create_empty_cnumpy_3x3_int_double_string();
    //then
    ASSERT_EXCEPTION({ empty_created.set_xy(-1, 0, 10); }, std::invalid_argument,
                     Exception_Cnumpy_Message::ACCESS_INDEX_MUST_BE_GREATER_OR_EQUAL_ZERO);
    ASSERT_EXCEPTION({ empty_created.set_xy(0, -1, 10); }, std::invalid_argument,
                     Exception_Cnumpy_Message::ACCESS_INDEX_MUST_BE_GREATER_OR_EQUAL_ZERO);
    ASSERT_EXCEPTION({ empty_created.set_xy(4, 0, 10); }, std::invalid_argument,
                     Exception_Cnumpy_Message::INDEXES_MUST_BE_SMALLER_THAN_DIMENSION_OF_CNUMPY);
    ASSERT_EXCEPTION({ empty_created.set_xy(1, 0, 10); }, std::invalid_argument,
                     Exception_Cnumpy_Message::VALUE_TYPE_DO_NOT_MATCH);
}

TEST(testCnumpy, get_unique_column_value) {

    //given
    Cnumpy data = create_empty_cnumpy_3x3_int_double_string();

    std::vector<int> int_column{10, 10, 30};
    std::vector<double> double_column{10.0, 30.0, 10.0};
    std::vector<std::string> string_column{"10", "20", "30"};

    data.set_column(0, int_column);
    data.set_column(1, double_column);
    data.set_column(2, string_column);

    //when
    Cnumpy unique_int_column_values = data.get_unique_column_values(0);
    Cnumpy unique_double_column_values = data.get_unique_column_values(1);
    Cnumpy unique_string_column_values = data.get_unique_column_values(2);

    //then
    EXPECT_EQ(2, unique_int_column_values.get_y_dimension());
    EXPECT_EQ(10, unique_int_column_values.get_xy_int(0, 0));
    EXPECT_EQ(30, unique_int_column_values.get_xy_int(0, 1));

    EXPECT_EQ(2, unique_double_column_values.get_y_dimension());
    ASSERT_DOUBLE_EQ(10.0, unique_double_column_values.get_xy_double(0, 0));
    ASSERT_DOUBLE_EQ(30.0, unique_double_column_values.get_xy_double(0, 1));

    EXPECT_EQ(3, unique_string_column_values.get_y_dimension());
    EXPECT_EQ("10", unique_string_column_values.get_xy_string(0, 0));
    EXPECT_EQ("20", unique_string_column_values.get_xy_string(0, 1));
    EXPECT_EQ("30", unique_string_column_values.get_xy_string(0, 2));


}

TEST(testCnumpy, get_min_value_in_column) {
    //given
    Cnumpy data = create_empty_cnumpy_3x3_int_double_string();

    std::vector<int> int_column{30, 10, 0};
    std::vector<double> double_column{20.0, 10.0, 30.0};
    std::vector<std::string> string_column{"aa", "cc", "xx"};

    //when
    data.set_column(0, int_column);
    data.set_column(1, double_column);
    data.set_column(2, string_column);


    Cnumpy min_int_value = data.get_min_value_in_column(0);
    Cnumpy min_double_value = data.get_min_value_in_column(1);
    Cnumpy min_string_value = data.get_min_value_in_column(2);

    //then
    EXPECT_EQ(0, min_int_value.get_xy_int(0, 0));
    ASSERT_DOUBLE_EQ(10.0, min_double_value.get_xy_double(0, 0));
    EXPECT_EQ("aa", min_string_value.get_xy_string(0, 0));

}

TEST(testCnumpy, get_max_value_in_column) {
    //given
    Cnumpy data = create_empty_cnumpy_3x3_int_double_string();

    std::vector<int> int_column{30, 10, 0};
    std::vector<double> double_column{20.0, 10.0, 30.0};
    std::vector<std::string> string_column{"aa", "cc", "xx"};

    //when
    data.set_column(0, int_column);
    data.set_column(1, double_column);
    data.set_column(2, string_column);

    Cnumpy max_int_value = data.get_max_value_in_column(0);
    Cnumpy max_double_value = data.get_max_value_in_column(1);
    Cnumpy max_string_value = data.get_max_value_in_column(2);


    //then
    EXPECT_EQ(30, max_int_value.get_xy_int(0, 0));
    ASSERT_DOUBLE_EQ(30.0, max_double_value.get_xy_double(0, 0));
    EXPECT_EQ("xx", max_string_value.get_xy_string(0, 0));

}


TEST(testCnumpy, get_xy_cnumpy) {
    //given
    Cnumpy data = create_fill_cnumpy_3x3_increased_value_int_double_string();

    //when
    Cnumpy value_int_0 = data.get_xy(0, 0);
    Cnumpy value_int_1 = data.get_xy(0, 1);
    Cnumpy value_int_2 = data.get_xy(0, 2);
    Cnumpy value_double_0 = data.get_xy(1, 0);
    Cnumpy value_double_1 = data.get_xy(1, 1);
    Cnumpy value_double_2 = data.get_xy(1, 2);
    Cnumpy value_string_0 = data.get_xy(2, 0);
    Cnumpy value_string_1 = data.get_xy(2, 1);
    Cnumpy value_string_2 = data.get_xy(2, 2);

    //then
    EXPECT_EQ(10, value_int_0.get_xy_int(0, 0));
    EXPECT_EQ(20, value_int_1.get_xy_int(0, 0));
    EXPECT_EQ(30, value_int_2.get_xy_int(0, 0));

    ASSERT_DOUBLE_EQ(10.0, value_double_0.get_xy_double(0, 0));
    ASSERT_DOUBLE_EQ(20.0, value_double_1.get_xy_double(0, 0));
    ASSERT_DOUBLE_EQ(30.0, value_double_2.get_xy_double(0, 0));

    EXPECT_EQ("10", value_string_0.get_xy_string(0, 0));
    EXPECT_EQ("20", value_string_1.get_xy_string(0, 0));
    EXPECT_EQ("30", value_string_2.get_xy_string(0, 0));


}


TEST(testCnumpy, get_xy_cnumpy_unallowed_index) {
    //given
    Cnumpy data = create_fill_cnumpy_3x3_increased_value_int_double_string();

    //then
    ASSERT_EXCEPTION({ data.get_xy_int(-1, 3); }, std::invalid_argument,
                     Exception_Cnumpy_Message::ACCESS_INDEX_MUST_BE_GREATER_OR_EQUAL_ZERO);
    ASSERT_EXCEPTION({ data.get_xy_int(5, 3); }, std::invalid_argument,
                     Exception_Cnumpy_Message::INDEXES_MUST_BE_SMALLER_THAN_DIMENSION_OF_CNUMPY);
    ASSERT_EXCEPTION({ data.get_xy_int(2, 2); }, std::invalid_argument,
                     Exception_Cnumpy_Message::VALUE_TYPE_DO_NOT_MATCH);

    ASSERT_EXCEPTION({ data.get_xy_double(-1, 3); }, std::invalid_argument,
                     Exception_Cnumpy_Message::ACCESS_INDEX_MUST_BE_GREATER_OR_EQUAL_ZERO);
    ASSERT_EXCEPTION({ data.get_xy_double(5, 3); }, std::invalid_argument,
                     Exception_Cnumpy_Message::INDEXES_MUST_BE_SMALLER_THAN_DIMENSION_OF_CNUMPY);
    ASSERT_EXCEPTION({ data.get_xy_double(0, 2); }, std::invalid_argument,
                     Exception_Cnumpy_Message::VALUE_TYPE_DO_NOT_MATCH);

    ASSERT_EXCEPTION({ data.get_xy_string(-1, 3); }, std::invalid_argument,
                     Exception_Cnumpy_Message::ACCESS_INDEX_MUST_BE_GREATER_OR_EQUAL_ZERO);
    ASSERT_EXCEPTION({ data.get_xy_string(5, 3); }, std::invalid_argument,
                     Exception_Cnumpy_Message::INDEXES_MUST_BE_SMALLER_THAN_DIMENSION_OF_CNUMPY);
    ASSERT_EXCEPTION({ data.get_xy_string(0, 2); }, std::invalid_argument,
                     Exception_Cnumpy_Message::VALUE_TYPE_DO_NOT_MATCH);
}

TEST(testCnumpy, of) {

    //when
    Cnumpy int_value_cnumpy = Cnumpy::of(5);
    Cnumpy double_value_cnumpy = Cnumpy::of(15.0);
    Cnumpy string_value_cnumpy = Cnumpy::of("text");

    //then
    EXPECT_EQ(5, int_value_cnumpy.get_xy_int(0, 0));
    EXPECT_EQ(1, int_value_cnumpy.get_y_dimension());
    EXPECT_EQ(1, int_value_cnumpy.get_x_dimension());


    ASSERT_DOUBLE_EQ(15.0, double_value_cnumpy.get_xy_double(0, 0));
    EXPECT_EQ(1, double_value_cnumpy.get_y_dimension());
    EXPECT_EQ(1, double_value_cnumpy.get_x_dimension());

    EXPECT_EQ("text", string_value_cnumpy.get_xy_string(0, 0));
    EXPECT_EQ(1, double_value_cnumpy.get_y_dimension());
    EXPECT_EQ(1, double_value_cnumpy.get_x_dimension());
}

TEST(testCnumpy, constructor_from_raw_value) {

    //when
    Cnumpy int_value_cnumpy(5);
    Cnumpy double_value_cnumpy(15.0);
    Cnumpy string_value_cnumpy("text");

    //then
    EXPECT_EQ(5, int_value_cnumpy.get_xy_int(0, 0));
    EXPECT_EQ(1, int_value_cnumpy.get_y_dimension());
    EXPECT_EQ(1, int_value_cnumpy.get_x_dimension());


    ASSERT_DOUBLE_EQ(15.0, double_value_cnumpy.get_xy_double(0, 0));
    EXPECT_EQ(1, double_value_cnumpy.get_y_dimension());
    EXPECT_EQ(1, double_value_cnumpy.get_x_dimension());

    EXPECT_EQ("text", string_value_cnumpy.get_xy_string(0, 0));
    EXPECT_EQ(1, double_value_cnumpy.get_y_dimension());
    EXPECT_EQ(1, double_value_cnumpy.get_x_dimension());
}


TEST(testCnumpy, operator_compare_differend_type) {
    //given
    Cnumpy int_value_10_cnumpy = Cnumpy::of(10);
    Cnumpy double_value_5_cnumpy = Cnumpy::of(5.0);

    //then
    ASSERT_EXCEPTION({ double_value_5_cnumpy < int_value_10_cnumpy; }, std::invalid_argument,
                     Exception_Cnumpy_Message::VALUE_TYPE_DO_NOT_MATCH);
    ASSERT_EXCEPTION({ double_value_5_cnumpy <= int_value_10_cnumpy; }, std::invalid_argument,
                     Exception_Cnumpy_Message::VALUE_TYPE_DO_NOT_MATCH);
    ASSERT_EXCEPTION({ double_value_5_cnumpy > int_value_10_cnumpy; }, std::invalid_argument,
                     Exception_Cnumpy_Message::VALUE_TYPE_DO_NOT_MATCH);
    ASSERT_EXCEPTION({ double_value_5_cnumpy >= int_value_10_cnumpy; }, std::invalid_argument,
                     Exception_Cnumpy_Message::VALUE_TYPE_DO_NOT_MATCH);
    ASSERT_EXCEPTION({ double_value_5_cnumpy == int_value_10_cnumpy; }, std::invalid_argument,
                     Exception_Cnumpy_Message::VALUE_TYPE_DO_NOT_MATCH);
    ASSERT_EXCEPTION({ double_value_5_cnumpy != int_value_10_cnumpy; }, std::invalid_argument,
                     Exception_Cnumpy_Message::VALUE_TYPE_DO_NOT_MATCH);
}


TEST(testCnumpy, operator_lower) {
    //given
    Cnumpy int_value_5_cnumpy = Cnumpy::of(5);
    Cnumpy int_value_10_cnumpy = Cnumpy::of(10);

    Cnumpy double_value_5_cnumpy = Cnumpy::of(5.0);
    Cnumpy double_value_10_cnumpy = Cnumpy::of(10.0);

    Cnumpy string_value_aa_cnumpy = Cnumpy::of("aa");
    Cnumpy string_value_bb_cnumpy = Cnumpy::of("bb");


    //then
    EXPECT_TRUE(int_value_5_cnumpy < int_value_10_cnumpy);
    EXPECT_TRUE(double_value_5_cnumpy < double_value_10_cnumpy);
    EXPECT_TRUE(string_value_aa_cnumpy < string_value_bb_cnumpy);

    EXPECT_FALSE(int_value_10_cnumpy < int_value_5_cnumpy);
    EXPECT_FALSE(double_value_10_cnumpy < double_value_5_cnumpy);
    EXPECT_FALSE(string_value_bb_cnumpy < string_value_aa_cnumpy);

    EXPECT_FALSE(int_value_10_cnumpy < int_value_10_cnumpy);
    EXPECT_FALSE(double_value_10_cnumpy < double_value_10_cnumpy);
    EXPECT_FALSE(string_value_bb_cnumpy < string_value_bb_cnumpy);


}

TEST(testCnumpy, operator_lower_or_equal) {
    //given
    Cnumpy int_value_5_cnumpy = Cnumpy::of(5);
    Cnumpy int_value_10_cnumpy = Cnumpy::of(10);

    Cnumpy double_value_5_cnumpy = Cnumpy::of(5.0);
    Cnumpy double_value_10_cnumpy = Cnumpy::of(10.0);

    Cnumpy string_value_aa_cnumpy = Cnumpy::of("aa");
    Cnumpy string_value_bb_cnumpy = Cnumpy::of("bb");

    //then
    EXPECT_TRUE(int_value_5_cnumpy <= int_value_10_cnumpy);
    EXPECT_TRUE(double_value_5_cnumpy <= double_value_10_cnumpy);
    EXPECT_TRUE(string_value_aa_cnumpy <= string_value_bb_cnumpy);

    EXPECT_FALSE(int_value_10_cnumpy <= int_value_5_cnumpy);
    EXPECT_FALSE(double_value_10_cnumpy <= double_value_5_cnumpy);
    EXPECT_FALSE(string_value_bb_cnumpy <= string_value_aa_cnumpy);

    EXPECT_TRUE(int_value_10_cnumpy <= int_value_10_cnumpy);
    EXPECT_TRUE(double_value_10_cnumpy <= double_value_10_cnumpy);
    EXPECT_TRUE(string_value_bb_cnumpy <= string_value_bb_cnumpy);


}

TEST(testCnumpy, operator_greater) {
    //given
    Cnumpy int_value_5_cnumpy = Cnumpy::of(5);
    Cnumpy int_value_10_cnumpy = Cnumpy::of(10);

    Cnumpy double_value_5_cnumpy = Cnumpy::of(5.0);
    Cnumpy double_value_10_cnumpy = Cnumpy::of(10.0);

    Cnumpy string_value_aa_cnumpy = Cnumpy::of("aa");
    Cnumpy string_value_bb_cnumpy = Cnumpy::of("bb");

    //then
    EXPECT_FALSE(int_value_5_cnumpy > int_value_10_cnumpy);
    EXPECT_FALSE(double_value_5_cnumpy > double_value_10_cnumpy);
    EXPECT_FALSE(string_value_aa_cnumpy > string_value_bb_cnumpy);

    EXPECT_TRUE(int_value_10_cnumpy > int_value_5_cnumpy);
    EXPECT_TRUE(double_value_10_cnumpy > double_value_5_cnumpy);
    EXPECT_TRUE(string_value_bb_cnumpy > string_value_aa_cnumpy);

    EXPECT_FALSE(int_value_10_cnumpy > int_value_10_cnumpy);
    EXPECT_FALSE(double_value_10_cnumpy > double_value_10_cnumpy);
    EXPECT_FALSE(string_value_bb_cnumpy > string_value_bb_cnumpy);


}

TEST(testCnumpy, operator_greater_or_equal) {
    //given
    Cnumpy int_value_5_cnumpy = Cnumpy::of(5);
    Cnumpy int_value_10_cnumpy = Cnumpy::of(10);

    Cnumpy double_value_5_cnumpy = Cnumpy::of(5.0);
    Cnumpy double_value_10_cnumpy = Cnumpy::of(10.0);

    Cnumpy string_value_aa_cnumpy = Cnumpy::of("aa");
    Cnumpy string_value_bb_cnumpy = Cnumpy::of("bb");


    //then
    EXPECT_FALSE(int_value_5_cnumpy >= int_value_10_cnumpy);
    EXPECT_FALSE(double_value_5_cnumpy >= double_value_10_cnumpy);
    EXPECT_FALSE(string_value_aa_cnumpy >= string_value_bb_cnumpy);

    EXPECT_TRUE(int_value_10_cnumpy >= int_value_5_cnumpy);
    EXPECT_TRUE(double_value_10_cnumpy >= double_value_5_cnumpy);
    EXPECT_TRUE(string_value_bb_cnumpy >= string_value_aa_cnumpy);

    EXPECT_TRUE(int_value_10_cnumpy >= int_value_10_cnumpy);
    EXPECT_TRUE(double_value_10_cnumpy >= double_value_10_cnumpy);
    EXPECT_TRUE(string_value_bb_cnumpy >= string_value_bb_cnumpy);


}


TEST(testCnumpy, operator_equal) {
    //given
    Cnumpy int_value_5_cnumpy = Cnumpy::of(5);
    Cnumpy int_value_10_cnumpy = Cnumpy::of(10);

    Cnumpy double_value_5_cnumpy = Cnumpy::of(5.0);
    Cnumpy double_value_10_cnumpy = Cnumpy::of(10.0);

    Cnumpy string_value_aa_cnumpy = Cnumpy::of("aa");
    Cnumpy string_value_bb_cnumpy = Cnumpy::of("bb");

    //then
    EXPECT_FALSE(int_value_5_cnumpy == int_value_10_cnumpy);
    EXPECT_FALSE(double_value_5_cnumpy == double_value_10_cnumpy);
    EXPECT_FALSE(string_value_aa_cnumpy == string_value_bb_cnumpy);

    EXPECT_TRUE(int_value_10_cnumpy == int_value_10_cnumpy);
    EXPECT_TRUE(double_value_10_cnumpy == double_value_10_cnumpy);
    EXPECT_TRUE(string_value_bb_cnumpy == string_value_bb_cnumpy);


}

TEST(testCnumpy, operator_not_equal) {
    //given
    Cnumpy int_value_5_cnumpy = Cnumpy::of(5);
    Cnumpy int_value_10_cnumpy = Cnumpy::of(10);

    Cnumpy double_value_5_cnumpy = Cnumpy::of(5.0);
    Cnumpy double_value_10_cnumpy = Cnumpy::of(10.0);

    Cnumpy string_value_aa_cnumpy = Cnumpy::of("aa");
    Cnumpy string_value_bb_cnumpy = Cnumpy::of("bb");

    //then
    EXPECT_TRUE(int_value_5_cnumpy != int_value_10_cnumpy);
    EXPECT_TRUE(double_value_5_cnumpy != double_value_10_cnumpy);
    EXPECT_TRUE(string_value_aa_cnumpy != string_value_bb_cnumpy);

    EXPECT_FALSE(int_value_10_cnumpy != int_value_10_cnumpy);
    EXPECT_FALSE(double_value_10_cnumpy != double_value_10_cnumpy);
    EXPECT_FALSE(string_value_bb_cnumpy != string_value_bb_cnumpy);


}


TEST(testCnumpy, mathematical_operation_differend_type) {
    //given
    Cnumpy double_value_5_cnumpy = Cnumpy::of(5.0);
    Cnumpy int_value_10_cnumpy = Cnumpy::of(10);


    //then

    ASSERT_EXCEPTION({ double_value_5_cnumpy += int_value_10_cnumpy; }, std::invalid_argument,
                     Exception_Cnumpy_Message::VALUE_TYPE_DO_NOT_MATCH);

    ASSERT_EXCEPTION({ double_value_5_cnumpy -= int_value_10_cnumpy; }, std::invalid_argument,
                     Exception_Cnumpy_Message::VALUE_TYPE_DO_NOT_MATCH);

    ASSERT_EXCEPTION({ double_value_5_cnumpy /= int_value_10_cnumpy; }, std::invalid_argument,
                     Exception_Cnumpy_Message::VALUE_TYPE_DO_NOT_MATCH);

    ASSERT_EXCEPTION({ double_value_5_cnumpy *= int_value_10_cnumpy; }, std::invalid_argument,
                     Exception_Cnumpy_Message::VALUE_TYPE_DO_NOT_MATCH);

    ASSERT_EXCEPTION({ double_value_5_cnumpy + int_value_10_cnumpy; }, std::invalid_argument,
                     Exception_Cnumpy_Message::VALUE_TYPE_DO_NOT_MATCH);

    ASSERT_EXCEPTION({ double_value_5_cnumpy * int_value_10_cnumpy; }, std::invalid_argument,
                     Exception_Cnumpy_Message::VALUE_TYPE_DO_NOT_MATCH);

    ASSERT_EXCEPTION({ double_value_5_cnumpy / int_value_10_cnumpy; }, std::invalid_argument,
                     Exception_Cnumpy_Message::VALUE_TYPE_DO_NOT_MATCH);

    ASSERT_EXCEPTION({ double_value_5_cnumpy - int_value_10_cnumpy; }, std::invalid_argument,
                     Exception_Cnumpy_Message::VALUE_TYPE_DO_NOT_MATCH);


}

TEST(testCnumpy, mathematical_operation_not_allowed_for_type_text) {
    //given
    Cnumpy text = Cnumpy::of("example text");

    //then
    ASSERT_EXCEPTION({ text -= text; }, std::invalid_argument,
                     Exception_Cnumpy_Message::TEXT_SUBTRACTION_OPERATION_IS_NOT_ALLOWED);
    ASSERT_EXCEPTION({ text /= text; }, std::invalid_argument,
                     Exception_Cnumpy_Message::TEXT_DIVIDE_OPERATION_IS_NOT_ALLOWED);
    ASSERT_EXCEPTION({ text *= text; }, std::invalid_argument,
                     Exception_Cnumpy_Message::TEXT_MULTIPLICATION_IS_NOT_ALLOWED);
}

TEST(testCnumpy, operator_add) {
    //given
    Cnumpy int_value_5_cnumpy = Cnumpy::of(5);
    Cnumpy int_value_10_cnumpy = Cnumpy::of(10);
    Cnumpy result_add_int = int_value_5_cnumpy + int_value_10_cnumpy;

    Cnumpy double_value_5_cnumpy = Cnumpy::of(5.0);
    Cnumpy double_value_10_cnumpy = Cnumpy::of(10.0);
    Cnumpy result_add_double = double_value_5_cnumpy + double_value_10_cnumpy;

    Cnumpy string_value_aa_cnumpy = Cnumpy::of("aa");
    Cnumpy string_value_bb_cnumpy = Cnumpy::of("bb");
    Cnumpy result_add_string = string_value_aa_cnumpy + string_value_bb_cnumpy;

    //then
    EXPECT_EQ(15, result_add_int.get_xy_int(0, 0));
    EXPECT_DOUBLE_EQ(15.0, result_add_double.get_xy_double(0, 0));
    EXPECT_EQ("aabb", result_add_string.get_xy_string(0, 0));

}


TEST(testCnumpy, operator_add_equal) {
    //given
    Cnumpy result_first_int_value_5_cnumpy = Cnumpy::of(5);
    Cnumpy int_value_10_cnumpy = Cnumpy::of(10);
    result_first_int_value_5_cnumpy += int_value_10_cnumpy;

    Cnumpy result_first_double_value_5_cnumpy = Cnumpy::of(5.0);
    Cnumpy double_value_10_cnumpy = Cnumpy::of(10.0);
    result_first_double_value_5_cnumpy += double_value_10_cnumpy;

    Cnumpy result_first_string_value_aa_cnumpy = Cnumpy::of("aa");
    Cnumpy string_value_bb_cnumpy = Cnumpy::of("bb");
    result_first_string_value_aa_cnumpy += string_value_bb_cnumpy;

    //then
    EXPECT_EQ(15, result_first_int_value_5_cnumpy.get_xy_int(0, 0));
    EXPECT_DOUBLE_EQ(15.0, result_first_double_value_5_cnumpy.get_xy_double(0, 0));
    EXPECT_EQ("aabb", result_first_string_value_aa_cnumpy.get_xy_string(0, 0));


}

TEST(testCnumpy, operator_minus_equal) {
    //given
    Cnumpy first_value_results_int = Cnumpy::of(5);
    Cnumpy second_value_int = Cnumpy::of(10);
    first_value_results_int -= second_value_int;

    Cnumpy first_value_results_double = Cnumpy::of(5.0);
    Cnumpy second_value_double = Cnumpy::of(10.0);
    first_value_results_double -= second_value_double;


    Cnumpy text = Cnumpy::of("text");

    //then
    EXPECT_EQ(-5, first_value_results_int.get_xy_int(0, 0));
    EXPECT_DOUBLE_EQ(-5.0, first_value_results_double.get_xy_double(0, 0));


}

TEST(testCnumpy, operator_devide_equal) {

    //given
    Cnumpy first_value_results_int = Cnumpy::of(5);
    Cnumpy second_value_int = Cnumpy::of(10);
    first_value_results_int /= second_value_int;

    Cnumpy first_value_results_double = Cnumpy::of(5.0);
    Cnumpy second_value_double = Cnumpy::of(10.0);
    first_value_results_double /= second_value_double;

    Cnumpy text = Cnumpy::of("text");


    //then
    EXPECT_EQ(0, first_value_results_int.get_xy_int(0, 0));
    EXPECT_DOUBLE_EQ(0.5, first_value_results_double.get_xy_double(0, 0));


}

TEST(testCnumpy, operator_multiply_equal) {
    Cnumpy first_value_results_int = Cnumpy::of(5);
    Cnumpy second_value_int = Cnumpy::of(10);
    first_value_results_int *= second_value_int;

    Cnumpy first_value_results_double = Cnumpy::of(5.0);
    Cnumpy second_value_double = Cnumpy::of(10.0);
    first_value_results_double *= second_value_double;

    Cnumpy text = Cnumpy::of("text");

    EXPECT_EQ(50, first_value_results_int.get_xy_int(0, 0));
    EXPECT_DOUBLE_EQ(50.0, first_value_results_double.get_xy_double(0, 0));


}


TEST(testCnumpy, raw_assignes_bad_type) {
    //given
    Cnumpy data_3x_3 = create_empty_cnumpy_3x3_int_double_string();
    Cnumpy one_column = data_3x_3[0];
    Cnumpy value = Cnumpy::of(5);
    Cnumpy results = create_fill_cnumpy_3x3_increased_value_int_double_string();

    //then
    ASSERT_EXCEPTION({ value = "text"; }, std::invalid_argument, Exception_Cnumpy_Message::VALUE_TYPE_DO_NOT_MATCH);

    ASSERT_EXCEPTION({ one_column = 10; }, std::invalid_argument,
                     Exception_Cnumpy_Message::OPERATION_ALLOWED_ONLY_FOR_SAME_MATRIX_DIMENSIONS);

    ASSERT_EXCEPTION({ results[0] = std::vector<double>(); }, std::invalid_argument,
                     Exception_Cnumpy_Message::OPERATION_ALLOWED_ONLY_FOR_SAME_MATRIX_DIMENSIONS);

    ASSERT_EXCEPTION({ results[0] = (std::vector<int>{2, 3}); }, std::invalid_argument,
                     Exception_Cnumpy_Message::OPERATION_ALLOWED_ONLY_FOR_SAME_MATRIX_DIMENSIONS);

    ASSERT_EXCEPTION({ results[0] = (std::vector<double>{2.0, 3.0, 4.0}); }, std::invalid_argument,
                     Exception_Cnumpy_Message::VALUE_TYPE_DO_NOT_MATCH);

    ASSERT_EXCEPTION({ (results[0]) = 10; }, std::invalid_argument,
                     Exception_Cnumpy_Message::OPERATION_ALLOWED_ONLY_FOR_SAME_MATRIX_DIMENSIONS);

    ASSERT_EXCEPTION({ results[0] = std::vector<double>(); }, std::invalid_argument,
                     Exception_Cnumpy_Message::OPERATION_ALLOWED_ONLY_FOR_SAME_MATRIX_DIMENSIONS);

    ASSERT_EXCEPTION({ results[0] = (std::vector<double>{2, 3}); }, std::invalid_argument,
                     Exception_Cnumpy_Message::OPERATION_ALLOWED_ONLY_FOR_SAME_MATRIX_DIMENSIONS);

    ASSERT_EXCEPTION({ results[0] = (std::vector<std::string>{"2.0", "3.0", "4.0"}); }, std::invalid_argument,
                     Exception_Cnumpy_Message::VALUE_TYPE_DO_NOT_MATCH);
    ASSERT_EXCEPTION({ (results[0]) = 10; }, std::invalid_argument,
                     Exception_Cnumpy_Message::OPERATION_ALLOWED_ONLY_FOR_SAME_MATRIX_DIMENSIONS);

    ASSERT_EXCEPTION({ results[0] = std::vector<std::string>(); }, std::invalid_argument,
                     Exception_Cnumpy_Message::OPERATION_ALLOWED_ONLY_FOR_SAME_MATRIX_DIMENSIONS);

    ASSERT_EXCEPTION({ results[0] = (std::vector<std::string>{"2", "3"}); }, std::invalid_argument,
                     Exception_Cnumpy_Message::OPERATION_ALLOWED_ONLY_FOR_SAME_MATRIX_DIMENSIONS);

    ASSERT_EXCEPTION({ results[2] = (std::vector<int>{1, 2, 3}); }, std::invalid_argument,
                     Exception_Cnumpy_Message::VALUE_TYPE_DO_NOT_MATCH);

    ASSERT_EXCEPTION({ (results[0]) = 10; }, std::invalid_argument,
                     Exception_Cnumpy_Message::OPERATION_ALLOWED_ONLY_FOR_SAME_MATRIX_DIMENSIONS);


    ASSERT_EXCEPTION({ value = "text"; }, std::invalid_argument, Exception_Cnumpy_Message::VALUE_TYPE_DO_NOT_MATCH);

    ASSERT_EXCEPTION({ data_3x_3 = "10"; }, std::invalid_argument,
                     Exception_Cnumpy_Message::OPERATION_ALLOWED_ONLY_FOR_SAME_MATRIX_DIMENSIONS);

    ASSERT_EXCEPTION({ data_3x_3 = 11; }, std::invalid_argument,
                     Exception_Cnumpy_Message::OPERATION_ALLOWED_ONLY_FOR_SAME_MATRIX_DIMENSIONS);
}

TEST(testCnumpy, operator_assign_raw_int) {
    //given
    Cnumpy value = Cnumpy::of(5);
    int raw_value_to_assign = 20;
    //when
    value = raw_value_to_assign;

    //then
    EXPECT_EQ(20, value.get_xy_int(0, 0));
    EXPECT_EQ(1, value.get_y_dimension());
    EXPECT_EQ(1, value.get_x_dimension());


}

TEST(testCnumpy, operator_assign_raw_vector_int) {

    //given
    std::vector<int> raw_column_int;
    raw_column_int.push_back(18);
    raw_column_int.push_back(28);
    raw_column_int.push_back(38);

    Cnumpy results = create_fill_cnumpy_3x3_increased_value_int_double_string();

    //when
    Cnumpy first_column = results[0];
    first_column = raw_column_int;

    //then
    EXPECT_EQ(18, first_column.get_xy_int(0, 0));
    EXPECT_EQ(28, first_column.get_xy_int(0, 1));
    EXPECT_EQ(38, first_column.get_xy_int(0, 2));

    EXPECT_EQ(10, results.get_xy_int(0, 0));
    EXPECT_EQ(20, results.get_xy_int(0, 1));
    EXPECT_EQ(30, results.get_xy_int(0, 2));


    EXPECT_DOUBLE_EQ(10.0, results.get_xy_double(1, 0));
    EXPECT_DOUBLE_EQ(20.0, results.get_xy_double(1, 1));
    EXPECT_DOUBLE_EQ(30.0, results.get_xy_double(1, 2));


    EXPECT_EQ("10", results.get_xy_string(2, 0));
    EXPECT_EQ("20", results.get_xy_string(2, 1));
    EXPECT_EQ("30", results.get_xy_string(2, 2));


    EXPECT_EQ(3, results.get_y_dimension());
    EXPECT_EQ(3, results.get_x_dimension());


}

TEST(testCnumpy, operator_assign_raw_vector_double) {
    //given
    std::vector<double> raw_column_int;
    raw_column_int.push_back(18.0);
    raw_column_int.push_back(28.0);
    raw_column_int.push_back(38.0);

    Cnumpy results = create_fill_cnumpy_3x3_increased_value_int_double_string();

    //when
    Cnumpy first_column = results[1];
    first_column = raw_column_int;


    //then
    EXPECT_DOUBLE_EQ(18.0, first_column.get_xy_double(0, 0));
    EXPECT_DOUBLE_EQ(28.0, first_column.get_xy_double(0, 1));
    EXPECT_DOUBLE_EQ(38.0, first_column.get_xy_double(0, 2));

    EXPECT_EQ(10, results.get_xy_int(0, 0));
    EXPECT_EQ(20, results.get_xy_int(0, 1));
    EXPECT_EQ(30, results.get_xy_int(0, 2));


    EXPECT_DOUBLE_EQ(10.0, results.get_xy_double(1, 0));
    EXPECT_DOUBLE_EQ(20.0, results.get_xy_double(1, 1));
    EXPECT_DOUBLE_EQ(30.0, results.get_xy_double(1, 2));


    EXPECT_EQ("10", results.get_xy_string(2, 0));
    EXPECT_EQ("20", results.get_xy_string(2, 1));
    EXPECT_EQ("30", results.get_xy_string(2, 2));


    EXPECT_EQ(3, results.get_y_dimension());
    EXPECT_EQ(3, results.get_x_dimension());


}

TEST(testCnumpy, operator_assign_raw_vector_string) {

    //given
    std::vector<std::string> raw_column_string;
    raw_column_string.emplace_back("18");
    raw_column_string.emplace_back("28");
    raw_column_string.emplace_back("38");

    Cnumpy results = create_fill_cnumpy_3x3_increased_value_int_double_string();

    //when
    Cnumpy first_column = results[2];
    first_column = raw_column_string;

    //then
    EXPECT_EQ("18", first_column.get_xy_string(0, 0));
    EXPECT_EQ("28", first_column.get_xy_string(0, 1));
    EXPECT_EQ("38", first_column.get_xy_string(0, 2));

    EXPECT_EQ(10, results.get_xy_int(0, 0));
    EXPECT_EQ(20, results.get_xy_int(0, 1));
    EXPECT_EQ(30, results.get_xy_int(0, 2));


    EXPECT_DOUBLE_EQ(10.0, results.get_xy_double(1, 0));
    EXPECT_DOUBLE_EQ(20.0, results.get_xy_double(1, 1));
    EXPECT_DOUBLE_EQ(30.0, results.get_xy_double(1, 2));


    EXPECT_EQ("10", results.get_xy_string(2, 0));
    EXPECT_EQ("20", results.get_xy_string(2, 1));
    EXPECT_EQ("30", results.get_xy_string(2, 2));


    EXPECT_EQ(3, results.get_y_dimension());
    EXPECT_EQ(3, results.get_x_dimension());


}

TEST(testCnumpy, operator_assign_raw_double) {
    //given
    Cnumpy value = Cnumpy::of(5.0);
    double raw_value_to_assign = 20;
    //when
    value = raw_value_to_assign;

    //then
    EXPECT_EQ(20.0, value.get_xy_double(0, 0));
    EXPECT_EQ(1, value.get_y_dimension());
    EXPECT_EQ(1, value.get_x_dimension());


}

TEST(testCnumpy, operator_assign_raw_string) {

    //given
    Cnumpy value = Cnumpy::of("5");
    std::string raw_value_to_assign = "20";

    //when
    value = raw_value_to_assign;


    //then
    EXPECT_EQ("20", value.get_xy_string(0, 0));
    EXPECT_EQ(1, value.get_y_dimension());
    EXPECT_EQ(1, value.get_x_dimension());


}


TEST(testCnumpy, operator_subtraction) {

    //given
    Cnumpy int_value_5_cnumpy = Cnumpy::of(5);
    Cnumpy int_value_10_cnumpy = Cnumpy::of(10);
    Cnumpy result_substract_int = int_value_5_cnumpy - int_value_10_cnumpy;

    Cnumpy double_value_5_cnumpy = Cnumpy::of(5.0);
    Cnumpy double_value_10_cnumpy = Cnumpy::of(10.0);
    //when
    Cnumpy result_substract_double = double_value_10_cnumpy - double_value_5_cnumpy;


    //then
    EXPECT_EQ(-5, result_substract_int.get_xy_int(0, 0));
    EXPECT_DOUBLE_EQ(5.0, result_substract_double.get_xy_double(0, 0));


}

TEST(testCnumpy, operator_divide) {
    //given
    Cnumpy int_value_5_cnumpy = Cnumpy::of(5);
    Cnumpy int_value_10_cnumpy = Cnumpy::of(10);


    Cnumpy double_value_5_cnumpy = Cnumpy::of(5.0);
    Cnumpy double_value_10_cnumpy = Cnumpy::of(10.0);

    //when
    Cnumpy result_substract_double = double_value_10_cnumpy / double_value_5_cnumpy;
    Cnumpy result_substract_int = int_value_5_cnumpy / int_value_10_cnumpy;

    //then
    EXPECT_EQ(0, result_substract_int.get_xy_int(0, 0));
    EXPECT_DOUBLE_EQ(2.0, result_substract_double.get_xy_double(0, 0));

}

TEST(testCnumpy, operator_multiple) {
    //given
    Cnumpy int_value_5_cnumpy = Cnumpy::of(5);
    Cnumpy int_value_10_cnumpy = Cnumpy::of(10);


    Cnumpy double_value_5_cnumpy = Cnumpy::of(5.0);
    Cnumpy double_value_10_cnumpy = Cnumpy::of(10.0);

    //when
    Cnumpy result_substract_double = double_value_10_cnumpy * double_value_5_cnumpy;
    Cnumpy result_substract_int = int_value_5_cnumpy * int_value_10_cnumpy;
    //then
    EXPECT_EQ(50, result_substract_int.get_xy_int(0, 0));
    EXPECT_DOUBLE_EQ(50.0, result_substract_double.get_xy_double(0, 0));

}

TEST(testCnumpy, operator_minus) {
    //when
    Cnumpy int_value_5_cnumpy = -Cnumpy::of(5);
    Cnumpy double_value_10_cnumpy = -Cnumpy::of(10.0);

    //then
    EXPECT_EQ(-5, (int_value_5_cnumpy).get_xy_int(0, 0));
    EXPECT_DOUBLE_EQ(-10.0, double_value_10_cnumpy.get_xy_double(0, 0));

}



TEST(testCnumpy,array_acces_operator_bad_indexes){
    Cnumpy data_3x3 = create_empty_cnumpy_3x3_int_double_string();

    ASSERT_EXCEPTION({ data_3x3[-1] = 11; }, std::invalid_argument,
                     Exception_Cnumpy_Message::ACCESS_INDEX_MUST_BE_GREATER_OR_EQUAL_ZERO);

    ASSERT_EXCEPTION({ data_3x3[77] = 11; }, std::invalid_argument,
                     Exception_Cnumpy_Message::INDEXES_MUST_BE_SMALLER_THAN_DIMENSION_OF_CNUMPY);

    ASSERT_EXCEPTION({ data_3x3[2][-1] = 11; }, std::invalid_argument,
                     Exception_Cnumpy_Message::ACCESS_INDEX_MUST_BE_GREATER_OR_EQUAL_ZERO);

    ASSERT_EXCEPTION({ data_3x3[2][11] = 11; }, std::invalid_argument,
                     Exception_Cnumpy_Message::INDEXES_MUST_BE_SMALLER_THAN_DIMENSION_OF_CNUMPY);

    ASSERT_EXCEPTION({ data_3x3[0][0][9] = 11; }, std::invalid_argument,
                     Exception_Cnumpy_Message::INDEXES_MUST_BE_SMALLER_THAN_DIMENSION_OF_CNUMPY);
}

TEST(testCnumpy, array_access_operator) {

    //given
    Cnumpy one_value_cnumpy = Cnumpy::of(5);

    Cnumpy cnumpy_n_n = create_fill_cnumpy_3x3_increased_value_int_double_string();

    //then
    Cnumpy int_rows = cnumpy_n_n[0];
    EXPECT_EQ(5, one_value_cnumpy[0].get_xy_int(0, 0));
    EXPECT_EQ(10, int_rows[0].get_xy_int(0, 0));
    EXPECT_EQ(20, int_rows[1].get_xy_int(0, 0));
    EXPECT_EQ(30, int_rows[2].get_xy_int(0, 0));

    EXPECT_DOUBLE_EQ(20.0, (cnumpy_n_n[1][1]).get_xy_double(0, 0));
    EXPECT_EQ("20", (cnumpy_n_n[2][1]).get_xy_string(0, 0));

}

TEST(testCnumpy,assign_raw_value){
    //given
    Cnumpy int_raw = Cnumpy::of(2);
    Cnumpy double_raw = Cnumpy::of(2.0);
    Cnumpy string_raw = Cnumpy::of("text");

    //when
    int_raw = 10;
    double_raw = 10.0;
    string_raw = std::string("texttext");

    //then
    ASSERT_EQ(10,int_raw.get_xy_int(0,0));
    ASSERT_EQ("texttext",string_raw.get_xy_string(0,0));
    ASSERT_DOUBLE_EQ(10.0,double_raw.get_xy_double(0,0));

}

TEST(testCnumpy,assign_raw_value_newly_create_object){
    //given
    Cnumpy int_raw = 10;
    Cnumpy double_raw = 10.0;
    Cnumpy string_raw = std::string("texttext");

    //then
    ASSERT_EQ(10,int_raw.get_xy_int(0,0));
    ASSERT_EQ("texttext",string_raw.get_xy_string(0,0));
    ASSERT_DOUBLE_EQ(10.0,double_raw.get_xy_double(0,0));

}

TEST(testCnumpy,assign_raw_value_bad_type){
    //given
    Cnumpy int_raw = Cnumpy::of(2);
    Cnumpy double_raw = Cnumpy::of(2.0);
    Cnumpy string_raw = Cnumpy::of("text");

    //then
    ASSERT_EXCEPTION({ int_raw = 9.0; }, std::invalid_argument,
                     Exception_Cnumpy_Message::VALUE_TYPE_DO_NOT_MATCH);
    ASSERT_EXCEPTION({ double_raw = 11;}, std::invalid_argument,
                     Exception_Cnumpy_Message::VALUE_TYPE_DO_NOT_MATCH);
    ASSERT_EXCEPTION({ string_raw = 10; }, std::invalid_argument,
                     Exception_Cnumpy_Message::VALUE_TYPE_DO_NOT_MATCH);


}

TEST(testCnumpy,set_raw_value){
    //given
    Cnumpy int_raw = Cnumpy::of(2);
    Cnumpy double_raw = Cnumpy::of(2.0);
    Cnumpy string_raw = Cnumpy::of("text");



    //when
    int_raw.set(10);
    double_raw.set(10.0);
    string_raw.set(std::string("texttext"));


    //then
    ASSERT_EQ(10,int_raw.get_xy_int(0,0));
    ASSERT_EQ("texttext",string_raw.get_xy_string(0,0));
    ASSERT_DOUBLE_EQ(10.0,double_raw.get_xy_double(0,0));

}


TEST(testCnumpy,set_raw_value_bad_type){
    //given
    Cnumpy int_raw = Cnumpy::of(2);
    Cnumpy double_raw = Cnumpy::of(2.0);
    Cnumpy string_raw = Cnumpy::of("text");

    //then
    ASSERT_EXCEPTION({ int_raw.set (9.0); }, std::invalid_argument,
                     Exception_Cnumpy_Message::VALUE_TYPE_DO_NOT_MATCH);
    ASSERT_EXCEPTION({ double_raw.set (11);}, std::invalid_argument,
                     Exception_Cnumpy_Message::VALUE_TYPE_DO_NOT_MATCH);
    ASSERT_EXCEPTION({ string_raw.set(10); }, std::invalid_argument,
                     Exception_Cnumpy_Message::VALUE_TYPE_DO_NOT_MATCH);


}



TEST(testCnumpy,set_raw_vector_values){
    //given
    Cnumpy data_3x_3 = create_empty_cnumpy_3x3_int_double_string();

    std::vector<int> int_column{100, 200, 300};
    std::vector<double> double_column{100.0, 200.0, 300.0};
    std::vector<std::string> string_column{"100", "200", "300"};

    Cnumpy int_cnumpy = data_3x_3[0];
    Cnumpy double_cnumpy = data_3x_3[1];
    Cnumpy string_cnumpy = data_3x_3[2];

    //when
    int_cnumpy.set(int_column);
    double_cnumpy.set(double_column);
    string_cnumpy.set(string_column);

    //then
    ASSERT_EQ(100,int_cnumpy.get_xy_int(0,0));
    ASSERT_EQ(200,int_cnumpy.get_xy_int(0,1));
    ASSERT_EQ(300,int_cnumpy.get_xy_int(0,2));

    ASSERT_DOUBLE_EQ(100.0,double_cnumpy.get_xy_double(0,0));
    ASSERT_DOUBLE_EQ(200.0,double_cnumpy.get_xy_double(0,1));
    ASSERT_DOUBLE_EQ(300.0,double_cnumpy.get_xy_double(0,2));

    ASSERT_EQ("100",string_cnumpy.get_xy_string(0,0));
    ASSERT_EQ("200",string_cnumpy.get_xy_string(0,1));
    ASSERT_EQ("300",string_cnumpy.get_xy_string(0,2));

}



TEST(testCnumpy,set_raw_vector_value_bad_type){
    //given
    Cnumpy data_3x_3 = create_empty_cnumpy_3x3_int_double_string();

    std::vector<int> int_column{100, 200, 300};
    std::vector<double> double_column{100.0, 200.0, 300.0};
    std::vector<std::string> string_column{"100", "200", "300"};

    Cnumpy int_cnumpy = data_3x_3[0];
    Cnumpy double_cnumpy = data_3x_3[1];
    Cnumpy string_cnumpy = data_3x_3[2];


    //then
    ASSERT_EXCEPTION({ int_cnumpy.set(double_column); }, std::invalid_argument,
                     Exception_Cnumpy_Message::VALUE_TYPE_DO_NOT_MATCH);

    ASSERT_EXCEPTION({ double_cnumpy.set(int_column); }, std::invalid_argument,
                     Exception_Cnumpy_Message::VALUE_TYPE_DO_NOT_MATCH);

    ASSERT_EXCEPTION({ string_cnumpy.set(int_column); }, std::invalid_argument,
                     Exception_Cnumpy_Message::VALUE_TYPE_DO_NOT_MATCH);


}

TEST(testCnumpy,set_raw_value_bad_dimesnion){
    //given
    Cnumpy int_raw = Cnumpy::of(24);
    Cnumpy double_raw = Cnumpy::of(24.0);
    Cnumpy string_raw = Cnumpy::of("texdsft");

    Cnumpy data_3x_3 = create_empty_cnumpy_3x3_int_double_string();

    std::vector<int> int_column{100, 200, 300};
    std::vector<double> double_column{100.0, 200.0, 300.0};
    std::vector<std::string> string_column{"100", "200", "300"};

    //then
    ASSERT_EXCEPTION({ int_raw.set (int_column); }, std::invalid_argument,
                     Exception_Cnumpy_Message::OPERATION_ALLOWED_ONLY_FOR_SAME_MATRIX_DIMENSIONS);
    ASSERT_EXCEPTION({ double_raw.set (double_column);}, std::invalid_argument,
                     Exception_Cnumpy_Message::OPERATION_ALLOWED_ONLY_FOR_SAME_MATRIX_DIMENSIONS);
    ASSERT_EXCEPTION({ string_raw.set(string_column); }, std::invalid_argument,
                     Exception_Cnumpy_Message::OPERATION_ALLOWED_ONLY_FOR_SAME_MATRIX_DIMENSIONS);

    ASSERT_EXCEPTION({ data_3x_3[0].set(10); }, std::invalid_argument,
                     Exception_Cnumpy_Message::OPERATION_ALLOWED_ONLY_FOR_SAME_MATRIX_DIMENSIONS);
    ASSERT_EXCEPTION({ data_3x_3[1].set (22.0);}, std::invalid_argument,
                     Exception_Cnumpy_Message::OPERATION_ALLOWED_ONLY_FOR_SAME_MATRIX_DIMENSIONS);
    ASSERT_EXCEPTION({ data_3x_3[2].set(std::string("raw")); }, std::invalid_argument,
                     Exception_Cnumpy_Message::OPERATION_ALLOWED_ONLY_FOR_SAME_MATRIX_DIMENSIONS);




}

TEST(testCnumpy,set_raw_value_with_xy_index){
    //given
    Cnumpy data_3x3 = create_empty_cnumpy_3x3_int_double_string();

    //when
    data_3x3.set(0,0,19);
    data_3x3.set(1,2,20.0);
    data_3x3.set(2,0,"21");

    //then
    ASSERT_EQ(19,data_3x3.get_xy_int(0,0));
    ASSERT_EQ(0,data_3x3.get_xy_int(0,1));
    ASSERT_EQ(0,data_3x3.get_xy_int(0,2));

    ASSERT_DOUBLE_EQ(20.0,data_3x3.get_xy_double(1,2));
    ASSERT_DOUBLE_EQ(0.0,data_3x3.get_xy_double(1,0));
    ASSERT_DOUBLE_EQ(0.0,data_3x3.get_xy_double(1,1));

    ASSERT_EQ("21",data_3x3.get_xy_string(2,0));
    ASSERT_EQ("",data_3x3.get_xy_string(2,1));
    ASSERT_EQ("",data_3x3.get_xy_string(2,2));


}

TEST(testCnumpy,set_raw_value_with_xy_index_bad_type){
    //given
    Cnumpy data_3x3 = create_empty_cnumpy_3x3_int_double_string();

    //then
    ASSERT_EXCEPTION({ data_3x3.set(0,0,10.5); }, std::invalid_argument,
                     Exception_Cnumpy_Message::VALUE_TYPE_DO_NOT_MATCH);
    ASSERT_EXCEPTION({ data_3x3.set (1,0,22);}, std::invalid_argument,
                     Exception_Cnumpy_Message::VALUE_TYPE_DO_NOT_MATCH);
    ASSERT_EXCEPTION({ data_3x3.set(2,0,7); }, std::invalid_argument,
                     Exception_Cnumpy_Message::VALUE_TYPE_DO_NOT_MATCH);


}

TEST(testCnumpy,set_raw_value_with_xy_index_bad_indexes){
    //given
    Cnumpy data_3x3 = create_empty_cnumpy_3x3_int_double_string();

    //then
    ASSERT_EXCEPTION({ data_3x3.set(-4,0,10.5); }, std::invalid_argument,
                     Exception_Cnumpy_Message::ACCESS_INDEX_MUST_BE_GREATER_OR_EQUAL_ZERO);
    ASSERT_EXCEPTION({ data_3x3.set (9,0,22);}, std::invalid_argument,
                     Exception_Cnumpy_Message::INDEXES_MUST_BE_SMALLER_THAN_DIMENSION_OF_CNUMPY);
    ASSERT_EXCEPTION({ data_3x3.set(0,-10,7); }, std::invalid_argument,
                     Exception_Cnumpy_Message::ACCESS_INDEX_MUST_BE_GREATER_OR_EQUAL_ZERO);


}


TEST(testCnumpy,set_raw_vector_with_x_index){
    //given
    Cnumpy data_3x3 = create_empty_cnumpy_3x3_int_double_string();
    std::vector<int> int_column{100, 200, 300};
    std::vector<double> double_column{100.0, 200.0, 300.0};
    std::vector<std::string> string_column{"100", "200", "300"};

    //when
    data_3x3.set(0,int_column);
    data_3x3.set(1,double_column);
    data_3x3.set(2,string_column);

    //then
    ASSERT_EQ(100,data_3x3.get_xy_int(0,0));
    ASSERT_EQ(200,data_3x3.get_xy_int(0,1));
    ASSERT_EQ(300,data_3x3.get_xy_int(0,2));


    ASSERT_DOUBLE_EQ(100.0,data_3x3.get_xy_double(1,0));
    ASSERT_DOUBLE_EQ(200.0,data_3x3.get_xy_double(1,1));
    ASSERT_DOUBLE_EQ(300.0,data_3x3.get_xy_double(1,2));

    ASSERT_EQ("100",data_3x3.get_xy_string(2,0));
    ASSERT_EQ("200",data_3x3.get_xy_string(2,1));
    ASSERT_EQ("300",data_3x3.get_xy_string(2,2));


}

TEST(testCnumpy,set_raw_vector_with_x_index_bad_type){
    //given
    Cnumpy data_3x3 = create_empty_cnumpy_3x3_int_double_string();
    std::vector<int> int_column{100, 200, 300};
    std::vector<double> double_column{100.0, 200.0, 300.0};
    std::vector<std::string> string_column{"100", "200", "300"};

    //then
    ASSERT_EXCEPTION({ data_3x3.set(0,string_column); }, std::invalid_argument,
                     Exception_Cnumpy_Message::VALUE_TYPE_DO_NOT_MATCH);
    ASSERT_EXCEPTION({ data_3x3.set (1,int_column);}, std::invalid_argument,
                     Exception_Cnumpy_Message::VALUE_TYPE_DO_NOT_MATCH);
    ASSERT_EXCEPTION({ data_3x3.set(2,double_column); }, std::invalid_argument,
                     Exception_Cnumpy_Message::VALUE_TYPE_DO_NOT_MATCH);


}

TEST(testCnumpy,set_raw_vector_with_x_index_bad_indexes){
    //given
    Cnumpy data_3x3 = create_empty_cnumpy_3x3_int_double_string();
    std::vector<int> int_column{100, 200, 300};
    std::vector<double> double_column{100.0, 200.0, 300.0};
    std::vector<std::string> string_column{"100", "200", "300"};
    //then
    ASSERT_EXCEPTION({ data_3x3.set(-1,int_column); }, std::invalid_argument,
                     Exception_Cnumpy_Message::ACCESS_INDEX_MUST_BE_GREATER_OR_EQUAL_ZERO);
    ASSERT_EXCEPTION({ data_3x3.set (10,int_column);}, std::invalid_argument,
                     Exception_Cnumpy_Message::INDEXES_MUST_BE_SMALLER_THAN_DIMENSION_OF_CNUMPY);

    ASSERT_EXCEPTION({ data_3x3.set(-10,double_column); }, std::invalid_argument,
                     Exception_Cnumpy_Message::ACCESS_INDEX_MUST_BE_GREATER_OR_EQUAL_ZERO);
    ASSERT_EXCEPTION({ data_3x3.set(10,double_column); }, std::invalid_argument,
                     Exception_Cnumpy_Message::INDEXES_MUST_BE_SMALLER_THAN_DIMENSION_OF_CNUMPY);


    ASSERT_EXCEPTION({ data_3x3.set(-5,string_column); }, std::invalid_argument,
                     Exception_Cnumpy_Message::ACCESS_INDEX_MUST_BE_GREATER_OR_EQUAL_ZERO);

    ASSERT_EXCEPTION({ data_3x3.set(30,double_column); }, std::invalid_argument,
                     Exception_Cnumpy_Message::INDEXES_MUST_BE_SMALLER_THAN_DIMENSION_OF_CNUMPY);



}

