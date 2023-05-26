//
// Created by Konrad on 23.05.2023.
//


#include "decision_tree/decision_tree.h"

#include "gtest/gtest.h"
TEST(test_decision_tree,get_index_column_wchich_max_profit){
    decision_tree tree;

    csv csv_reader;
    Cnumpy data = csv_reader.read_cnumpy_from_csv("C:\\Users\\konra\\Documents\\PVM_Projekt\\randomforest\\RandomForest\\datasets\\tests\\data.csv", ",");
    int index_first = tree.get_index_column_with_max_information_profit(data, 0, 2);
    int index_second = tree.get_index_column_with_max_information_profit(data, 1, 2);

    ASSERT_EQ(0,index_first);
    ASSERT_EQ(1,index_second);

}

TEST(test_decision_tree,get_index_column_wchich_max_profit_if_working_for_iris_datasets){
    decision_tree tree;

    csv csv_reader;
    Cnumpy data = csv_reader.read_cnumpy_from_csv("C:\\Users\\konra\\Documents\\PVM_Projekt\\randomforest\\RandomForest\\datasets\\iris\\data.csv", ",");
    int index_first = tree.get_index_column_with_max_information_profit(data, 0, 2);
    int index_second = tree.get_index_column_with_max_information_profit(data, 1, 2);

    ASSERT_EQ(0,index_first);
    ASSERT_EQ(3,index_second);
}


//construct_general_tree

TEST(test_decision_tree,construct_tree){
    decision_tree tree;

    csv csv_reader;
    Cnumpy data = csv_reader.read_cnumpy_from_csv("C:\\Users\\konra\\Documents\\PVM_Projekt\\randomforest\\RandomForest\\datasets\\treedata\\data.csv", ",");
   tree_node x =  tree.construct_general_tree(data,2);

   std::cout<<x.get_name();
   std::cout<<"KONIEC";

}

TEST(test_decision_tree,construct_tree_and_predict){
    decision_tree tree;

    csv csv_reader;
    Cnumpy data = csv_reader.read_cnumpy_from_csv("C:\\Users\\konra\\Documents\\PVM_Projekt\\randomforest\\RandomForest\\datasets\\treedata\\data.csv", ",");


    tree_node x =  tree.construct_general_tree(data,2);



    std::vector<Type> string_column{Type::integer_type,Type::integer_type,Type::integer_type};

   Cnumpy elem(data.get_x_dimension(),1,string_column);
   elem.set(0,0,2);
   elem.set(1,0,1);
   elem.set(2,0,1);


    tree.returnReturnLabel(x,elem);

    std::cout<<"KONIEC";

}

TEST(test_decision_tree,construct_tree_and_predict_iris){
    decision_tree tree;

    csv csv_reader;
    Cnumpy data = csv_reader.read_cnumpy_from_csv("C:\\Users\\konra\\Documents\\PVM_Projekt\\randomforest\\RandomForest\\datasets\\iris_subset\\data.csv", ",");


    tree_node x =  tree.construct_general_tree(data,4);

//5.4,3.7,1.5,.2,"Setosa"

    std::vector<Type> string_column{Type::double_type,Type::double_type,Type::double_type,Type::double_type,Type::string_type};

    Cnumpy elem(5,1,string_column);
    elem.set(0,0,6.5);
    elem.set(1,0,3.0);
    elem.set(2,0,5.2);
    elem.set(3,0,2.0);
    elem.set(4,0,"Setosa");


    tree.returnReturnLabel(x,elem);

    std::cout<<"KONIEC";

}