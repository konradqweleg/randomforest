
#include "gtest/gtest.h"
#include "cnumpy/cnumpy.h"
#include "quant/quant.h"

//CNUMPY_quant_column_double_betweeen_method_result_avg_group
//To linkowanie jest złe

TEST(quant_tests, quant_double_column) {
    std::cout<<"x";
    std::vector<double> double_column{30.0, 29.9, 20.0,10.0,31.0,40.0,50.0,16.0};
    std::cout<<"x";
    Cnumpy data = Cnumpy::of(double_column);
    std::cout<<data;
    Cnumpy result = quant_utility::quant_column_double_betweeen_method_result_avg_group(data,0,1600);
//
   std::cout<<result;

}