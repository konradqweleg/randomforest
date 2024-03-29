//
// Created by konra on 25.04.2023.
//
#include "gtest/gtest.h"
#include "../csv/csv.h"
#include "../csv/csv.cpp"
#include "../csv/read_csv/ReadCSVBuffered.cpp"
#include "../csv/read_csv/ReadCSV_EachMethodOpenCloseFile.h"
#include "../csv/read_csv/ReadCSV_EachMethodOpenCloseFile.cpp"
#include "path_to_files.h"




std::vector<std::string> create_pattern_column_name_from_iris_datasets(){
    std::vector<std::string> expected_columns_name;
    expected_columns_name.emplace_back("sepal.length");
    expected_columns_name.emplace_back("sepal.width");
    expected_columns_name.emplace_back("petal.length");
    expected_columns_name.emplace_back("petal.width");
    expected_columns_name.emplace_back("variety");
    return expected_columns_name;
}


std::vector<Type> create_pattern_column_type_for_iris_datasets(){
    std::vector<Type> expected_column_type;
    expected_column_type.emplace_back(Type::double_type);
    expected_column_type.emplace_back(Type::double_type);
    expected_column_type.emplace_back(Type::double_type);
    expected_column_type.emplace_back(Type::double_type);
    expected_column_type.emplace_back(Type::string_type);
    return expected_column_type;
}

const int column_in_iris_datasets = 5;
const int rows_in_iris_datasets = 150;

TEST(test_csv,read_csv_buffered){
    csv csv_with_buffered_reader(new ReadCSVBuffered());
    Cnumpy read_data = csv_with_buffered_reader.read_cnumpy_from_csv(path_to_file::FULL_IRIS_DATASETS,",");

    std::vector<std::string> iris_columns_name = read_data.get_column_name();
    std::vector<std::string> expected_columns_name = create_pattern_column_name_from_iris_datasets();
    ASSERT_EQ(expected_columns_name,iris_columns_name);


    std::vector<Type> iris_column_type = read_data.get_type_columns();
    std::vector<Type> expected_column_type = create_pattern_column_type_for_iris_datasets();
    ASSERT_EQ(expected_column_type,iris_column_type);


    ASSERT_EQ(column_in_iris_datasets,read_data.get_x_dimension());
    ASSERT_EQ(rows_in_iris_datasets,read_data.get_y_dimension());

    ASSERT_DOUBLE_EQ(4.9,read_data.get_xy_double(0,9));
    ASSERT_DOUBLE_EQ(3.1,read_data.get_xy_double(1,9));
    ASSERT_DOUBLE_EQ(1.5,read_data.get_xy_double(2,9));
    ASSERT_DOUBLE_EQ(0.1,read_data.get_xy_double(3,9));
    ASSERT_EQ("Setosa",read_data.get_xy_string(4,9));

    ASSERT_EQ("Virginica",read_data.get_xy_string(4,100));
    ASSERT_DOUBLE_EQ(7.7,read_data.get_xy_double(0,135));
    ASSERT_DOUBLE_EQ(1.2,read_data.get_xy_double(3,90));

}

TEST(test_csv,read_csv_each_function_open_close_file){
    csv csv_with_buffered_reader(new ReadCSV_EachMethodOpenCloseFile());
    Cnumpy read_data = csv_with_buffered_reader.read_cnumpy_from_csv(path_to_file::FULL_IRIS_DATASETS,",");

    std::vector<std::string> iris_columns_name = read_data.get_column_name();
    std::vector<std::string> expected_columns_name = create_pattern_column_name_from_iris_datasets();
    ASSERT_EQ(expected_columns_name,iris_columns_name);


    std::vector<Type> iris_column_type = read_data.get_type_columns();
    std::vector<Type> expected_column_type = create_pattern_column_type_for_iris_datasets();
    ASSERT_EQ(expected_column_type,iris_column_type);


    ASSERT_EQ(column_in_iris_datasets,read_data.get_x_dimension());
    ASSERT_EQ(rows_in_iris_datasets,read_data.get_y_dimension());

    ASSERT_DOUBLE_EQ(4.9,read_data.get_xy_double(0,9));
    ASSERT_DOUBLE_EQ(3.1,read_data.get_xy_double(1,9));
    ASSERT_DOUBLE_EQ(1.5,read_data.get_xy_double(2,9));
    ASSERT_DOUBLE_EQ(0.1,read_data.get_xy_double(3,9));
    ASSERT_EQ("Setosa",read_data.get_xy_string(4,9));

    ASSERT_EQ("Virginica",read_data.get_xy_string(4,100));
    ASSERT_DOUBLE_EQ(7.7,read_data.get_xy_double(0,135));
    ASSERT_DOUBLE_EQ(1.2,read_data.get_xy_double(3,90));

}

