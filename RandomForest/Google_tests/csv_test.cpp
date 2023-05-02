//
// Created by konra on 25.04.2023.
//
#include "gtest/gtest.h"
#include "../csv/csv.h"
#include "../csv/csv.cpp"
#include "../cnumpy/cnumpy.h"
#include "../csv/read_csv/ReadCSVBuffered.h"
#include "../csv/read_csv/ReadCSVBuffered.cpp"
#include "../csv/read_csv/ReadCSV.h"
std::string path_to_iris_test_csv_file = "C:\\Users\\Konrad\\Documents\\repo\\randomforrest\\randomforest\\RandomForest\\Google_tests\\test_data\\iris.csv";

TEST(test_csv,read_csv_buffered){
    csv csv_with_buffered_reader(new ReadCSVBuffered());
    Cnumpy read_data = csv_with_buffered_reader.read_cnumpy_from_csv(path_to_iris_test_csv_file,",");

    std::vector<std::string> iris_columns_name = read_data.get_column_name();
    std::vector<std::string> expected_columns_name;
    expected_columns_name.push_back("sepal.length");
    expected_columns_name.push_back("sepal.width");
    expected_columns_name.push_back("petal.length");
    expected_columns_name.push_back("petal.width");
    expected_columns_name.push_back("variety");
    ASSERT_EQ(expected_columns_name,iris_columns_name);


    std::vector<Type> iris_column_type = read_data.get_type_columns();
    std::vector<Type> expected_column_type;
    expected_column_type.push_back(Type::double_type);
    expected_column_type.push_back(Type::double_type);
    expected_column_type.push_back(Type::double_type);
    expected_column_type.push_back(Type::double_type);
    expected_column_type.push_back(Type::string_type);
    ASSERT_EQ(expected_column_type,iris_column_type);


    ASSERT_EQ(5,read_data.get_x_dimension());
    ASSERT_EQ(150,read_data.get_y_dimension());

    ASSERT_DOUBLE_EQ(4.9,read_data.get_xy_double(0,9));
    ASSERT_DOUBLE_EQ(3.1,read_data.get_xy_double(1,9));
    ASSERT_DOUBLE_EQ(1.5,read_data.get_xy_double(2,9));
    ASSERT_DOUBLE_EQ(0.1,read_data.get_xy_double(3,9));
    ASSERT_EQ("Setosa",read_data.get_xy_string(4,9));

    ASSERT_EQ("Virginica",read_data.get_xy_string(4,100));
    ASSERT_DOUBLE_EQ(7.7,read_data.get_xy_double(0,135));
    ASSERT_DOUBLE_EQ(1.2,read_data.get_xy_double(3,90));



    std::cout<<read_data;

}

