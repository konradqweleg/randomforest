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

   // std::cout<<"111->"<<std::endl;
  //  std::cout<<row;
    Cnumpy result = tree.predict(root, row);
  //  std::cout<<"222->"<<std::endl;
    return result;

}

Cnumpy create_test_datasets(){
    std::vector<Type> columns_in_iris_datasets{Type::double_type, Type::double_type, Type::double_type, Type::double_type, Type::string_type};
    Cnumpy iris_test_data(5, 15, columns_in_iris_datasets);
    std::vector<double> sepal_length{
            5.0,5.4,5.8,6.0,6.3,6.8,6.5,7.7,7.7,0.5,0.5,0.5,0.5,0.4,0.5
    };

    std::vector<double> sepal_width{
            3.6,3.7,4.0,2.2,2.5,2.8,3.0,3.8,2.6,0.1,0.2,0.2,0.1,0.1,0.1
    };

    std::vector<double> petal_length{
            1.4,1.5,1.2,4.0,4.9,4.8,5.5,6.7,6.9,0.6,0.6,0.9,0.5,0.5,0.5
    };

    std::vector<double> petal_width{
            0.2,0.2,0.2,1.0,1.5,1.4,1.8,2.2,2.3,0.6,0.6,0.8,0.1,0.1,0.1
    };

    std::vector<std::string> label{
            "Setosa","Setosa","Setosa","Versicolor","Versicolor","Versicolor","Virginica","Virginica","Virginica","Ranunculus","Ranunculus","Ranunculus",
            "Bellis perennis","Bellis perennis","Bellis perennis"
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
     //   std::cout<<"x1"<<std::endl;
        Cnumpy prediction = predict_value_from_dataset(datasets,root,tree,i);
      //  std::cout<<"x2"<<std::endl;
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

    Cnumpy data = csv_reader.read_cnumpy_from_csv(path_to_file::IRIS_SUBSET, ",");//1
    std::cout<<data; //2
    tree_node root =  tree.construct_general_tree(data, 4);//3

    Cnumpy test_data = create_test_datasets(); //4
    double percent_correct = count_effectiveness(test_data,root,tree);//5
    std::cout<<"Model Efficiency = "<<percent_correct<<std::endl;//6
    Cnumpy result_label =  compare_result_to_expected_result(test_data,root,tree);//7
    std::cout<<result_label<<std::endl;//8
}



void check_forrest_prediction(int number_tree,int number_of_line){
    set_global_strategy_for_cnumpy();

    create_data_set create_dataset;

    //1
    create_dataset.create_files(number_tree,path_to_file::IRIS_SUBSET,number_of_line,"C:\\Users\\Konrad\\CLionProjects\\randomforest\\RandomForest\\Google_tests\\test_data\\datasets_for_random_forrest_splited\\");
    std::vector<Cnumpy> predicts_all;

    for(int i=0;i<number_tree;++i){
        //2
        decision_tree tree;
        csv csv_reader;
        //3
        Cnumpy data = csv_reader.read_cnumpy_from_csv("C:\\Users\\Konrad\\CLionProjects\\randomforest\\RandomForest\\Google_tests\\test_data\\datasets_for_random_forrest_splited\\"+std::to_string(i)+"\\data.csv", ",");
        //4
        tree_node root =  tree.construct_general_tree(data, 4);
        //5
        Cnumpy test_data = create_test_datasets();
        //6
        Cnumpy result_label =  compare_result_to_expected_result(test_data,root,tree);//to
        predicts_all.push_back(result_label);//to
    }


    int number =1;

    std::vector<Type> result_columns_type{Type::string_type, Type::integer_type,Type::integer_type,Type::integer_type,Type::integer_type,Type::integer_type,Type::integer_type,Type::string_type};
    std::vector<std::string> result_columns_name{"Expected","EMPTY","Setosa","Versricolor","Virginica","Ranunculus","Bellis perennis","Predicted"};

    Cnumpy results (8, 15, result_columns_type,result_columns_name);
    for(Cnumpy data:predicts_all){
        std::cout<<std::endl<<"Drzewo numer"<<number<<" wyniki "<<std::endl;
        std::cout<<data;

        for(int j=0;j<15;++j){
            Cnumpy predicted = data[1][j];

            if(predicted.get_xy_string(0,0) == "BRAK"){
                results.set(1,j,results[1][j].get_xy_int(0,0)+1);
            }else if(predicted.get_xy_string(0,0) == "Setosa" ){
                results.set(2,j,results[2][j].get_xy_int(0,0)+1);
            }else if(predicted.get_xy_string(0,0) == "Versicolor" ){
                results.set(3,j, results[3][j].get_xy_int(0,0)+1);
            }else if( predicted.get_xy_string(0,0) == "Ranunculus"){
                results.set(5,j, results[5][j].get_xy_int(0,0)+1);
            }else if( predicted.get_xy_string(0,0) == "Bellis perennis"){
                results.set(6,j, results[6][j].get_xy_int(0,0)+1);
            }
            else{
                results.set(4,j, results[4][j].get_xy_int(0,0)+1);
            }
            results.set(0,j,data[0][j]);

        }

        number++;
    }

    for(int y=0;y<results.get_y_dimension();++y){

        std::cout<<y<<std::endl;
        Cnumpy empty = results[1][y];
        Cnumpy setosa = results [2][y];
        Cnumpy versicolor = results[3][y];
        Cnumpy virginica = results[4][y];
        Cnumpy rananculus = results[5][y];
        Cnumpy bellis_perennis = results[6][y];
        std::cout<<y<<std::endl;
        if(empty > setosa && empty > versicolor  && empty >virginica && empty > rananculus && empty > bellis_perennis){
            int random_index = rand() % 5;

            if(random_index == 0){
                results.set(7,y,"Setosa");
            }else if(random_index ==1){
                results.set(7,y,"Versicolor");
            }else if(random_index ==2) {
                results.set(7,y,"Virginica");
            } else if(random_index == 3){
                results.set(7,y,"Ranunculus");
            }else{
                results.set(7,y,"Bellis perennis");
            }

        }else if(setosa > empty && setosa > versicolor && setosa > virginica && setosa > rananculus && setosa > bellis_perennis){
            results.set(7,y,"Setosa");
        }else if(versicolor >empty && versicolor > setosa && versicolor >virginica && versicolor > rananculus && versicolor > bellis_perennis){
            results.set(7,y,"Versicolor");
        }else if(virginica > empty && virginica >setosa && virginica > versicolor && virginica > rananculus && virginica > bellis_perennis){
            results.set(7,y,"Virginica");
        }else if(rananculus > empty && rananculus >setosa && rananculus > versicolor && rananculus > bellis_perennis && rananculus > virginica){
            results.set(7,y,"Ranunculus");
        }
        else if(bellis_perennis > empty && bellis_perennis >setosa && bellis_perennis > versicolor && bellis_perennis > rananculus && bellis_perennis > virginica){
            results.set(7,y,"Bellis perennis");
        }
        else{
            int random_index = rand() % 5;

            if(random_index == 0){
                results.set(7,y,"Setosa");
            }else if(random_index ==1){
                results.set(7,y,"Versicolor");
            }else if(random_index ==2) {
                results.set(7,y,"Virginica");
            } else if(random_index == 3){
                results.set(7,y,"Ranunculus");
            }else{
                results.set(7,y,"Bellis perennis");
            }
        }





    }




    std::cout<<"WYNIKI CALOSCI"<<std::endl;
    std::cout<<results;



    int correct_answers=0;
    for(int k=0;k<results.get_y_dimension();++k){

        Cnumpy expected = results[0][k];
        Cnumpy predicted = results[7][k];
        if(expected == predicted){
            correct_answers++;
        }
    }
    std::cout<<"Skutecznosc modelu to  "<< ((double )correct_answers)/((double )results.get_y_dimension())  <<std::endl;


}

void temp(){
    csv csv_reader;

    Cnumpy data = csv_reader.read_cnumpy_from_csv("C:\\Users\\Konrad\\Documents\\repo\\randomforrest\\randomforest\\RandomForest\\Google_tests\\test_data\\datasets_for_random_forrest_splited\\"+std::to_string(2)+"\\data.csv", ",");
    std::cout<<data;
}


void one_tree(){
    auto start = high_resolution_clock::now();
    check_one_tree_prediction();
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);

    std::cout << "Time taken by function: "
              << duration.count() << " microseconds" << std::endl;
}

void forrest(){
    auto start = high_resolution_clock::now();
    check_forrest_prediction(5,80);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);

    std::cout << "Time taken by function: "
              << duration.count() << " microseconds" << std::endl;
}

int main() {
    forrest();

}




