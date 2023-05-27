//
// Created by Konrad on 23.05.2023.
//


#include "decision_tree/decision_tree.h"

#include "gtest/gtest.h"
#include "path_to_files.h"
TEST(test_decision_tree,get_index_column_wchich_max_profit){
    decision_tree tree;

    csv csv_reader;
    Cnumpy data = csv_reader.read_cnumpy_from_csv(path_to_file::CALCULATION_DATA, ",");
    int index_first = tree.get_index_column_with_max_information_profit(data, 0, 2);
    int index_second = tree.get_index_column_with_max_information_profit(data, 1, 2);

    ASSERT_EQ(0,index_first);
    ASSERT_EQ(1,index_second);

}

TEST(test_decision_tree,get_index_column_wchich_max_profit_if_working_for_iris_datasets){
    decision_tree tree;

    csv csv_reader;
    Cnumpy data = csv_reader.read_cnumpy_from_csv(path_to_file::FULL_IRIS_DATASETS, ",");
    int index_first = tree.get_index_column_with_max_information_profit(data, 0, 2);
    int index_second = tree.get_index_column_with_max_information_profit(data, 1, 2);

    ASSERT_EQ(0,index_first);
    ASSERT_EQ(3,index_second);
}


TEST(test_decision_tree,construct_tree){
    decision_tree tree;

    csv csv_reader;
    Cnumpy data = csv_reader.read_cnumpy_from_csv(path_to_file::CALCULATION_DATA, ",");
    tree_node root =  tree.construct_general_tree(data, 2);
    Cnumpy first_child_value = root.get_children()[0].get_value();
    Cnumpy second_child_value = root.get_children()[1].get_value();
    Cnumpy third_child_value = root.get_children()[2].get_value();

    ASSERT_EQ(3, root.get_children().size());
    ASSERT_TRUE(root.is_root());
    ASSERT_FALSE(root.is_leaf());

    ASSERT_EQ(0,first_child_value.get_xy_int(0,0));
    ASSERT_EQ(1,second_child_value.get_xy_int(0,0));
    ASSERT_EQ(2,third_child_value.get_xy_int(0,0));

}

TEST(test_decision_tree,construct_tree_and_predict){
    decision_tree tree;

    csv csv_reader;
    Cnumpy data = csv_reader.read_cnumpy_from_csv(path_to_file::CALCULATION_DATA, ",");


    tree_node root =  tree.construct_general_tree(data, 2);

    std::vector<Type> string_column{Type::integer_type,Type::integer_type,Type::integer_type};
    Cnumpy value_to_predict(data.get_x_dimension(), 1, string_column);
    value_to_predict.set(0, 0, 2);
    value_to_predict.set(1, 0, 1);
    value_to_predict.set(2, 0, 1);


    Cnumpy predict = tree.predict_verbose(root, value_to_predict);
    std::cout<<predict;
    //to do check results

}

TEST(test_decision_tree,construct_tree_and_predict_iris_subset){
    decision_tree tree;

    csv csv_reader;
    Cnumpy data = csv_reader.read_cnumpy_from_csv(path_to_file::IRIS_SUBSET, ",");
    tree_node root =  tree.construct_general_tree(data, 4);

    std::vector<Type> string_column{Type::double_type,Type::double_type,Type::double_type,Type::double_type,Type::string_type};

    Cnumpy elem(5,1,string_column);
    elem.set(0,0,6.9);
    elem.set(1,0,3.1);
    elem.set(2,0,4.9);
    elem.set(3,0,1.5);
    elem.set(4,0,"?");

    Cnumpy result = tree.predict(root, elem);
    ASSERT_EQ("BRAK",result.get_xy_string(0,0));

}