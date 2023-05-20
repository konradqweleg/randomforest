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
#include "cnumpy/math/histogram_base.h"



TEST(entropy_tests,calculate_entropy_all_data_based_on_column_prepared_data){

    histogram* hist_strategy = new histogram_base();
    Cnumpy::set_histogram_calculation_strategy(hist_strategy);

    Entropy entropy_strategy;
    csv csv_reader;
    Cnumpy data_for_test_entropy = csv_reader.read_cnumpy_from_csv("C:\\Users\\Konrad\\Documents\\repo\\randomforrest\\randomforest\\RandomForest\\datasets\\tests\\data.csv", ",");
    Cnumpy entropy_predict_column = entropy_strategy.CNUMPY_calculate_entropy_all_data_based_on_column(data_for_test_entropy,2);

    ASSERT_DOUBLE_EQ(0.65002242164835411,entropy_predict_column.get_xy_double(0,0));

}


TEST(entropy_tests,calculate_entropy_all_data_based_on_column_iris_dataset_if_calculate_results){

    histogram* hist_strategy = new histogram_base();
    Cnumpy::set_histogram_calculation_strategy(hist_strategy);

    Entropy entropy_strategy;
    csv csv_reader;
    Cnumpy data_for_test_entropy = csv_reader.read_cnumpy_from_csv("C:\\Users\\Konrad\\Documents\\repo\\randomforrest\\randomforest\\RandomForest\\datasets\\iris\\data.csv", ",");
    Cnumpy entropy_predict_column = entropy_strategy.CNUMPY_calculate_entropy_all_data_based_on_column(data_for_test_entropy,2);

}