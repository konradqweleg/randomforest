//
// Created by Konrad on 23.05.2023.
//


#include "decision_tree/decision_tree.h"

#include "gtest/gtest.h"
TEST(test_decision_tree,get_index_column_wchich_max_profit){
    decision_tree tree;

    csv csv_reader;
    Cnumpy data = csv_reader.read_cnumpy_from_csv("C:\\Users\\Konrad\\Documents\\repo\\randomforrest\\randomforest\\RandomForest\\datasets\\tests\\data.csv", ",");
    int index_first = tree.get_index_column_with_max_information_profit(data, 0, 2);
    int index_second = tree.get_index_column_with_max_information_profit(data, 1, 2);

    ASSERT_EQ(0,index_first);
    ASSERT_EQ(1,index_second);

}

TEST(test_decision_tree,get_index_column_wchich_max_profit_if_working_for_iris_datasets){
    decision_tree tree;

    csv csv_reader;
    Cnumpy data = csv_reader.read_cnumpy_from_csv("C:\\Users\\Konrad\\Documents\\repo\\randomforrest\\randomforest\\RandomForest\\datasets\\iris\\data.csv", ",");
    int index_first = tree.get_index_column_with_max_information_profit(data, 0, 2);
    int index_second = tree.get_index_column_with_max_information_profit(data, 1, 2);

    ASSERT_EQ(0,index_first);
    ASSERT_EQ(3,index_second);
}


//construct_general_tree

TEST(test_decision_tree,construct_tree){
    decision_tree tree;

    csv csv_reader;
    Cnumpy data = csv_reader.read_cnumpy_from_csv("C:\\Users\\Konrad\\Documents\\repo\\randomforrest\\randomforest\\RandomForest\\datasets\\treedata\\data.csv", ",");
    tree.construct_general_tree(data,2);


}