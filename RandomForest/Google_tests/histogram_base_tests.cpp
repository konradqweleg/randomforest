//
// Created by Konrad on 19.05.2023.
//

#include "../cnumpy/math/histogram.h"
#include "../cnumpy/math/histogram_base.cpp"
#include "gtest/gtest.h"


//To linkowanie jest złe
Cnumpy create_empty_cnumpy_3x3_int_double_string();

TEST(test_base_histogram, hist) {

    //given
    Cnumpy data = create_empty_cnumpy_3x3_int_double_string();

    std::vector<int> int_column{10, 10, 30};
    std::vector<double> double_column{10.0, 10.0, 10.0};
    std::vector<std::string> string_column{"10", "20", "30"};
    data.set_column(0, int_column);
    data.set_column(1, double_column);
    data.set_column(2, string_column);

    histogram&& hist_calculator = histogram_base();
    //when
    Cnumpy histogram_column_number_0 = hist_calculator.hist(data, 0);
    Cnumpy histogram_column_number_1 = hist_calculator.hist(data, 1);
    Cnumpy histogram_column_number_2 = hist_calculator.hist(data, 2);

    //then
    ASSERT_EQ(2,histogram_column_number_0.get_x_dimension());
    ASSERT_EQ(2,histogram_column_number_0.get_y_dimension());

    ASSERT_EQ(2,histogram_column_number_1.get_x_dimension());
    ASSERT_EQ(1,histogram_column_number_1.get_y_dimension());

    ASSERT_EQ(2,histogram_column_number_2.get_x_dimension());
    ASSERT_EQ(3,histogram_column_number_2.get_y_dimension());


    ASSERT_EQ(10,histogram_column_number_0[0][0].get_xy_int(0,0));
    ASSERT_EQ(30,histogram_column_number_0[0][1].get_xy_int(0,0));
    ASSERT_EQ(2,histogram_column_number_0[1][0].get_xy_int(0,0));
    ASSERT_EQ(1,histogram_column_number_0[1][1].get_xy_int(0,0));


    ASSERT_DOUBLE_EQ(10.0,histogram_column_number_1[0][0].get_xy_double(0,0));
    ASSERT_EQ(3,histogram_column_number_1[1][0].get_xy_int(0,0));


    ASSERT_EQ("10",histogram_column_number_2[0][0].get_xy_string(0,0));
    ASSERT_EQ("20",histogram_column_number_2[0][1].get_xy_string(0,0));
    ASSERT_EQ("30",histogram_column_number_2[0][2].get_xy_string(0,0));

    ASSERT_EQ(1,histogram_column_number_2[1][0].get_xy_int(0,0));
    ASSERT_EQ(1,histogram_column_number_2[1][1].get_xy_int(0,0));
    ASSERT_EQ(1,histogram_column_number_2[1][2].get_xy_int(0,0));





}