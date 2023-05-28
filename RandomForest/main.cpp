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
#include "create_data_set.h"



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


Cnumpy compare_result_to_expected_result(Cnumpy datasets,tree_node root,decision_tree tree){

    std::vector<Type> result_columns_type{Type::string_type, Type::string_type,Type::string_type};
    std::vector<std::string> result_columns_name{"Expected","Predict","STATUS"};

    Cnumpy results (3, datasets.get_y_dimension(), result_columns_type,result_columns_name);

    for(int i=0;i<datasets.get_y_dimension();++i){
        Cnumpy prediction = predict_value_from_dataset(datasets,root,tree,i);

        Cnumpy correct_row_prediction = datasets[4][i];
        results.set(0,i, correct_row_prediction);
        results.set(1,i, prediction);

        if(correct_row_prediction == prediction){
           results.set(2,i,"MATCH");
        }else{
           results.set(2,i,"MISMATCH");
        }

    }

    return results;

}

void check_one_tree_prediction(){
    set_global_strategy_for_cnumpy();

    decision_tree tree;

    csv csv_reader;
    Cnumpy data = csv_reader.read_cnumpy_from_csv(path_to_file::IRIS_SUBSET, ",");
    tree_node root =  tree.construct_general_tree(data, 4);

    Cnumpy test_data = create_test_datasets();
    double percent_correct = count_effectiveness(test_data,root,tree);
    std::cout<<"Model Efficiency = "<<percent_correct<<std::endl;
    Cnumpy result_label =  compare_result_to_expected_result(test_data,root,tree);
    std::cout<<result_label<<std::endl;
}



void check_forrest_prediction(){
    create_data_set create_dataset;
    create_dataset.create_files(10,path_to_file::IRIS_SUBSET,120,"C:\\Users\\konra\\Documents\\PVM_Projekt\\randomforest\\RandomForest\\Google_tests\\test_data\\datasets_for_random_forrest_splited");

}

int main() {
    check_forrest_prediction();


}




