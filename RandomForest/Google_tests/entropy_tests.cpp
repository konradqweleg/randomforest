//
// Created by Konrad on 20.05.2023.
//

#include "gtest/gtest.h"

#include <iostream>
#include "cnumpy/cnumpy.h"
#include "csv/csv.h"
#include "csv/read_csv//ReadCSV.h"
#include "csv/read_csv//ReadCSVBuffered.h"
#include "csv/read_csv/ReadCSV_EachMethodOpenCloseFile.h"
#include "entropy/Entropy.h"
#include "entropy/Entropy.cpp"
#include "cnumpy/math/histogram_base.h"
#include "path_to_files.h"


TEST(entropy_tests,calculate_entropy_all_data_based_on_column_prepared_data){

    histogram* hist_strategy = new histogram_base();
    Cnumpy::set_histogram_calculation_strategy(hist_strategy);

    Entropy entropy_strategy;
    csv csv_reader;
    Cnumpy data_for_test_entropy = csv_reader.read_cnumpy_from_csv(path_to_file::CALCULATION_DATA, ",");
    Cnumpy entropy_predict_column = entropy_strategy.calculate_entropy_all_data_based_on_column(data_for_test_entropy,
                                                                                                2);

    ASSERT_DOUBLE_EQ(0.65002242164835411,entropy_predict_column.get_xy_double(0,0));

}


TEST(entropy_tests,calculate_entropy_all_data_based_on_column_iris_dataset_if_calculate_results){

    histogram* hist_strategy = new histogram_base();
    Cnumpy::set_histogram_calculation_strategy(hist_strategy);

    Entropy entropy_strategy;
    csv csv_reader;
    Cnumpy data_for_test_entropy = csv_reader.read_cnumpy_from_csv(path_to_file::FULL_IRIS_DATASETS, ",");
    Cnumpy entropy_predict_column = entropy_strategy.calculate_entropy_all_data_based_on_column(data_for_test_entropy,
                                                                                                2);

}



TEST(entropy_tests,calculate_entropy_for_columns){

    histogram* hist_strategy = new histogram_base();
    Cnumpy::set_histogram_calculation_strategy(hist_strategy);

    Entropy entropy_strategy;
    csv csv_reader;
    Cnumpy data_for_test_entropy = csv_reader.read_cnumpy_from_csv(path_to_file::CALCULATION_DATA, ",");
    Cnumpy entropy_for_columns_0 = entropy_strategy.calculate_entropy_for_columns(data_for_test_entropy, 0, 2);
    Cnumpy entropy_for_columns_1 = entropy_strategy.calculate_entropy_for_columns(data_for_test_entropy, 1, 2);
    ASSERT_DOUBLE_EQ(0.33333333333333331,entropy_for_columns_0.get_xy_double(0,0));
    ASSERT_DOUBLE_EQ(0.45914791702724478,entropy_for_columns_1.get_xy_double(0,0));
}

TEST(entropy_tests,calculate_entropy_for_columns_iris_dataset_if_calculate_results){

    histogram* hist_strategy = new histogram_base();
    Cnumpy::set_histogram_calculation_strategy(hist_strategy);

    Entropy entropy_strategy;
    csv csv_reader;
    Cnumpy data_for_test_entropy = csv_reader.read_cnumpy_from_csv(path_to_file::FULL_IRIS_DATASETS, ",");

    Cnumpy entropy_for_columns_0 = entropy_strategy.calculate_entropy_for_columns(data_for_test_entropy, 0, 4);
    Cnumpy entropy_for_columns_1 = entropy_strategy.calculate_entropy_for_columns(data_for_test_entropy, 1, 4);
    Cnumpy entropy_for_columns_2 = entropy_strategy.calculate_entropy_for_columns(data_for_test_entropy, 2, 4);
    Cnumpy entropy_for_columns_3 = entropy_strategy.calculate_entropy_for_columns(data_for_test_entropy, 3, 4);


}



TEST(entropy_tests,calculate_information_profit_for_columns){

    histogram* hist_strategy = new histogram_base();
    Cnumpy::set_histogram_calculation_strategy(hist_strategy);

    Entropy entropy_strategy;
    csv csv_reader;
    Cnumpy data_for_test_entropy = csv_reader.read_cnumpy_from_csv(path_to_file::CALCULATION_DATA, ",");
    Cnumpy entropy_for_columns_0 = entropy_strategy.calculate_information_profit_for_column(data_for_test_entropy, 0, 2);
    Cnumpy entropy_for_columns_1 = entropy_strategy.calculate_information_profit_for_column(data_for_test_entropy, 1, 2);
    ASSERT_DOUBLE_EQ(0.31668908831502079,entropy_for_columns_0.get_xy_double(0,0));
    ASSERT_DOUBLE_EQ(0.19087450462110933,entropy_for_columns_1.get_xy_double(0,0));
}

TEST(entropy_tests,calculate_information_profiyt_for_columns_iris_dataset_if_calculate_results){

    histogram* hist_strategy = new histogram_base();
    Cnumpy::set_histogram_calculation_strategy(hist_strategy);

    Entropy entropy_strategy;
    csv csv_reader;
    Cnumpy data_for_test_entropy = csv_reader.read_cnumpy_from_csv(path_to_file::FULL_IRIS_DATASETS, ",");

    Cnumpy entropy_for_columns_0 = entropy_strategy.calculate_information_profit_for_column(data_for_test_entropy, 0, 4);
    Cnumpy entropy_for_columns_1 = entropy_strategy.calculate_information_profit_for_column(data_for_test_entropy, 1, 4);
    Cnumpy entropy_for_columns_2 = entropy_strategy.calculate_information_profit_for_column(data_for_test_entropy, 2, 4);
    Cnumpy entropy_for_columns_3 = entropy_strategy.calculate_information_profit_for_column(data_for_test_entropy, 3, 4);



}