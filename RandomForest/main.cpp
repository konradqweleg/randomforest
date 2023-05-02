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

int main() {

    csv xa(new ReadCSVBuffered());


    auto start = high_resolution_clock::now();
    Cnumpy xdd = xa.read_cnumpy_from_csv (
            "C:\\Users\\Konrad\\Documents\\repo\\randomforrest\\randomforest\\RandomForest\\datasets\\iris\\data.csv",
            ",");
    auto stop = high_resolution_clock::now();
     auto duration = duration_cast<microseconds>(stop - start);

      std::cout << "Time taken by function: "
          << duration.count() << " microseconds" << std::endl;



    std::cout << xdd;
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