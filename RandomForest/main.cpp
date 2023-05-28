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
#include "Google_tests/path_to_files.h"
#include "Google_tests//path_to_files.cpp"



void set_global_strategy_for_cnumpy(){
    histogram* hist_strategy = new histogram_base();
    Cnumpy::set_histogram_calculation_strategy(hist_strategy);
}
Cnumpy predict_value_from_dataset(Cnumpy datasets,tree_node root,decision_tree tree,int index_y){
    std::vector<Type> columns_in_iris_datasets{Type::double_type, Type::double_type, Type::double_type, Type::double_type, Type::string_type};
    Cnumpy row(5, 1, columns_in_iris_datasets);
    row.set(0, 0, datasets[0][index_y]);
    row.set(1, 0, datasets[1][index_y]);
    row.set(2, 0, datasets[2][index_y]);
    row.set(3, 0, datasets[3][index_y]);
    row.set(4, 0, datasets[4][index_y]);

    Cnumpy result = tree.predict(root, row);
    return result;

}

Cnumpy create_test_datasets(){
    std::vector<Type> columns_in_iris_datasets{Type::double_type, Type::double_type, Type::double_type, Type::double_type, Type::string_type};
    Cnumpy iris_test_data(5, 10, columns_in_iris_datasets);

    std::vector<double> sepal_length{
            4.6,4.6,5.5,6.9,5.9,5.4,6.2,6,6.5,7.7
    };

    std::vector<double> sepal_width{
            3.4,3.6,4.3,3.1,3.2,3.0,2.9,3.0,3.0,3.0
    };

    std::vector<double> petal_length{
            1.4,1.0,1.4,4.9,4.8,4.5,4.3,4.8,5.2,6.1
    };

    std::vector<double> petal_width{
            0.3,0.2,0.2,1.5,1.8,1.5,1.3,1.8,2.0,2.3
    };

    std::vector<std::string> label{
            "Setosa","Setosa","Setosa","Versicolor","Versicolor","Versicolor","Versicolor","Virginica","Virginica","Virginica"
    };

    iris_test_data.set(0, sepal_length);
    iris_test_data.set(1, sepal_width);
    iris_test_data.set(2, petal_length);
    iris_test_data.set(3, petal_width);
    iris_test_data.set(4, label);

    return iris_test_data;


}

double count_effectiveness(Cnumpy datasets,tree_node root,decision_tree tree){
    int correct_response = 0;


    for(int i=0;i<datasets.get_y_dimension();++i){
        Cnumpy prediction = predict_value_from_dataset(datasets,root,tree,i);

        Cnumpy correct_row_prediction = datasets[4][i];
        if(prediction == correct_row_prediction){
            correct_response++;

        }

    }

    return ((double)correct_response)/ ((double) datasets.get_y_dimension());

}

int main() {
    set_global_strategy_for_cnumpy();

    decision_tree tree;

    csv csv_reader;
    Cnumpy data = csv_reader.read_cnumpy_from_csv(path_to_file::IRIS_SUBSET, ",");
    tree_node root =  tree.construct_general_tree_verbose(data, 4);

    Cnumpy test_data = create_test_datasets();
    double percent_correct = count_effectiveness(test_data,root,tree);
    std::cout<<"Skutecznosc modelu to = "<<percent_correct<<std::endl;

   // std::vector<Type> string_column{Type::double_type,Type::double_type,Type::double_type,Type::double_type,Type::string_type};

//    Cnumpy elem(5,1,string_column);
//    elem.set(0,0,6.9);
//    elem.set(1,0,3.1);
//    elem.set(2,0,4.9);
//    elem.set(3,0,1.5);
//    elem.set(4,0,"?");
//
//    Cnumpy result = tree.predict(root, elem);
//    std::cout<<result<<std::endl;



}




