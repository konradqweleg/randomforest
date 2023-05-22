
#include "gtest/gtest.h"
#include "cnumpy/cnumpy.h"
#include "quant/quant.h"
#include "csv/csv.h"
#include "entropy/Entropy.h"
#include "cnumpy/math/histogram_base.h"



TEST(quant_tests, quant_double_column) {
    std::vector<double> double_column{30.0, 5.0,12.5,19.0,90.0};
    Cnumpy data = Cnumpy::of(double_column);
    Cnumpy result = quant_utility::quant_column_double_betweeen_method_result_avg_group(data,0,2);
    ASSERT_DOUBLE_EQ(42.5,result.get_xy_double(0,0));
    ASSERT_DOUBLE_EQ(42.5,result.get_xy_double(0,1));
    ASSERT_DOUBLE_EQ(42.5,result.get_xy_double(0,2));
    ASSERT_DOUBLE_EQ(42.5,result.get_xy_double(0,3));
    ASSERT_DOUBLE_EQ(85,result.get_xy_double(0,4));

}


TEST(quant_tests,quant_double_column_if_calculate_for_iris_dataset){
    histogram* hist_strategy = new histogram_base();
    Cnumpy::set_histogram_calculation_strategy(hist_strategy);

    csv csv_reader;
    Cnumpy data_for_test_entropy = csv_reader.read_cnumpy_from_csv("C:\\Users\\Konrad\\Documents\\repo\\randomforrest\\randomforest\\RandomForest\\datasets\\iris\\data.csv", ",");

    Cnumpy results = quant_utility::quant_column_double_betweeen_method_result_avg_group(data_for_test_entropy,0,10);


}