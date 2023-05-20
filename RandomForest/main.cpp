#include <iostream>
#include "cnumpy/cnumpy.h"
#include "type.h"
#include "csv/csv.h"
#include <chrono>

using namespace std::chrono;

#include <fstream>
#include "decision_tree/decision_tree.h"
#include "quant/quant.h"
#include "csv/read_csv//ReadCSV.h"
#include "csv/read_csv//ReadCSVBuffered.h"
#include "csv/read_csv/ReadCSV_EachMethodOpenCloseFile.h"
#include "entropy/Entropy.h"
#include "cnumpy/math/histogram_base.h"



void set_global_strategy_for_cnumpy(){
    histogram* hist_strategy = new histogram_base();
    Cnumpy::set_histogram_calculation_strategy(hist_strategy);
}

int main() {
    set_global_strategy_for_cnumpy();

    csv csv_calc;
    Cnumpy data_for_test_entropy = csv_calc.read_cnumpy_from_csv("C:\\Users\\Konrad\\Documents\\repo\\randomforrest\\randomforest\\RandomForest\\datasets\\tests\\data.csv",",");
    Cnumpy hist_column =  data_for_test_entropy.hist(0);
    std::cout<<hist_column;


    Entropy entropy_calc;
    std::cout<<entropy_calc.calculate_entropy_all_data_based_on_column(data_for_test_entropy,0)<<std::endl;
    std::cout<<entropy_calc.CNUMPY_calculate_entropy_all_data_based_on_column(data_for_test_entropy,0)<<std::endl;


  //  Cnumpy xd = Cnumpy::of(100);
    //xd.set_xy(0,0,10);
  //  xd.set(10);
//   std::cout<<data_for_test_entropy.get_xy(0,0);
   // std::cout<<data_for_test_entropy;
//    std::cout<<data_for_test_entropy<< std::endl;

  //  Cnumpy data = data_for_test_entropy.hist(2);
  //  std::cout<<data;
//    Cnumpy m_v= data_for_test_entropy.get_min_value_in_column(2);
//    Cnumpy m_v_2= data_for_test_entropy.get_min_value_in_column(1);
//    std::cout<<std::endl;
//    std::cout<<m_v;
//    std::cout<<std::endl;
//    std::cout<<m_v_2;
//    std::cout<<std::endl;
//    std::cout<<(m_v<m_v_2);
//    std::cout<<(m_v>m_v_2);

//    data_for_test_entropy.get_column_raw(0,1);
//
//    Cnumpy xd =data_for_test_entropy.get_unique_column_values(0);
//    std::cout<<xd;

//    std::cout<<data_for_test_entropy;
//    Entropy x;
//    std::cout<<std::endl;
//    double entropy =  x.calculate_entropy_all_data_based_on_column(data_for_test_entropy,0);
//
//    std::cout<<"Entropy : "<<entropy<<std::endl;
//
//    double xqwa= x.calculate_information_gain_for_column(data_for_test_entropy, 0, 2);
//    std::cout<<" Zysk informacyjny : "<<xqwa<<std::endl;









































  /*  csv xa(new ReadCSVBuffered());


    auto start = high_resolution_clock::now();
    Cnumpy xdd = xa.read_cnumpy_from_csv (
            "C:\\Users\\Konrad\\Documents\\repo\\randomforrest\\randomforest\\RandomForest\\datasets\\iris\\data.csv",
            ",");
    auto stop = high_resolution_clock::now();
     auto duration = duration_cast<microseconds>(stop - start);

      std::cout << "Time taken by function: "
          << duration.count() << " microseconds" << std::endl;



    std::cout << xdd;*/
    //

//    //Cnumpy test
//
//    std::vector<Type> typeCol = std::vector<Type>();
//    typeCol.push_back(Type::integer_type);
//    typeCol.push_back(Type::double_type);
//    typeCol.push_back(Type::integer_type);
//    typeCol.push_back(Type::integer_type);
//    typeCol.push_back(Type::integer_type);
//
//    std::vector<std::string> nameC = std::vector<std::string>();
//    nameC.push_back("name");
//    nameC.push_back("xd");
//    nameC.push_back("xd");
//    nameC.push_back("xd2");
//    nameC.push_back("xd3");
//
//    Cnumpy data = Cnumpy(5,5,typeCol,nameC);
//
//    data.set_xy(1,1,2.0);
//    data.set_xy(2,0,1);
//    data.set_xy(3,0,2);
//    data.set_xy(4,3,3);
//
//    std::vector<int> x;
//    x.push_back(-9);
//    x.push_back(-9);
//    x.push_back(-9);
//    x.push_back(-9);
//    x.push_back(-9);
//
//
//    data.set_column(0, x);
//
//
//
//   // std::cout<<data;
//
//
//
//
//
//
//






    //  auto start = high_resolution_clock::now();
    // Cnumpy xd = csv::read_csv_file_as_cnumpy("C:\\Users\\Konrad\\Documents\\repo\\randomforrest\\randomforest\\RandomForest\\datasets\\iris\\data.csv");
    // auto stop = high_resolution_clock::now();

    // Get duration. Substart timepoints to
    // get duration. To cast it to proper unit
    // use duration cast method
    // auto duration = duration_cast<microseconds>(stop - start);

    //  std::cout << "Time taken by function: "
    //      << duration.count() << " microseconds" << std::endl;
    // std::cout<<xd;




//
//   std::vector<double> col_1 = xd.get_column_double<double>(0);
//   col_1 = quant_utility::quant_column_double_betweeen_method_result_avg_group(col_1,0.10);
//
//    xd.set_column(0, col_1);
//
//
//   std::cout<<xd<<std::endl;
//
//
//   // decision_tree::quant_data_in_cnumpy(xd,0.10,"xd");
//
//
//    std::vector<int> result_column = xd.get_column_double<int>(2);
//
//    //std::vector<std::string> xdd =xd.get_column_double<std::string>(3);
//
//
//    for(int a : result_column){
//        std::cout<<a<<std::endl;
//    }
//
//    std::cout<<"Entropia rezultat : "<<decision_tree::entropy_result(result_column)<<std::endl;
//
//    std::map<int,double> entropy = decision_tree::entropy_for_column(xd.get_column_double<int>(1), result_column);
//
//
//    for(std::map<int,double>::iterator iter = entropy.begin(); iter != entropy.end(); ++iter)
//    {
//        int k =  iter->first;
//
//        double v = iter->second;
//        std::cout<<"Key = "<<k<<" Value = "<<v<<std::endl;
//    }
//
//
//    std::map<int,int> awx = decision_tree::how_many_key_in_results(result_column);
//    for(std::map<int,int>::iterator iter = awx.begin(); iter != awx.end(); ++iter)
//    {
//        int k =  iter->first;
//
//        int v = iter->second;
//        std::cout<<"Key_1 = "<<k<<" Value_1 = "<<v<<std::endl;
//    }
//
//
//    std::cout<<"Profit : "<<decision_tree::get_information_profit(entropy, xd.get_column_double<int>(1), result_column);
//
//
//    std::cout<<"Gotowe";



}