//
// Created by Konrad on 13.04.2023.
//

#ifndef RANDOMFOREST_DECISION_TREE_H
#define RANDOMFOREST_DECISION_TREE_H

#include "tree_node.h"
#include "../cnumpy/cnumpy.h"
#include <string>
#include <set>
#include <map>
#include <cmath>
#include "cnumpy/math/histogram_base.h"
#include "entropy/Entropy.h"
#include "csv/csv.h"
#include <map>
#include <vector>
#include <algorithm>
#include <iostream>
#include <utility>
#include <functional>
class decision_tree {


public:



    static bool sortByVal(const std::pair<int, double> &a, const std::pair<int, double> &b){
        return a.second > b.second;
    }

    int get_index_column_with_max_information_profit(Cnumpy data, int which_number, int predict_column){
        histogram* hist_strategy = new histogram_base();
        Cnumpy::set_histogram_calculation_strategy(hist_strategy);
        Entropy entropy_strategy;

        std::map<int,double> index_column_information_profit;

        for(int i=0;i<data.get_x_dimension();++i){

            if(i==predict_column){
                continue;
            }

            Cnumpy information_profit_for_column = entropy_strategy.calculate_information_profit_for_column(data, i, predict_column);
            index_column_information_profit[i] = information_profit_for_column.get_xy_double(0, 0);

        }


        std::vector<std::pair<int, double>> index_column_information_profit_vector;
        for(auto m: index_column_information_profit){
            index_column_information_profit_vector.push_back(std::make_pair(m.first, m.second));
        }


        sort(index_column_information_profit_vector.begin(), index_column_information_profit_vector.end(), sortByVal);

        return index_column_information_profit_vector[which_number].first;

    }






    tree_node create_lower_level_tree(Cnumpy data, tree_node& node, int predict_column_index){


        int number_column_max_profit_for_level = node.get_level();
        int max_index_profit_for_level_column = get_index_column_with_max_information_profit(data, number_column_max_profit_for_level, predict_column_index);

        if(node.is_root()){
            Cnumpy unique_values_in_column = data.get_unique_column_values(max_index_profit_for_level_column);

            for(int i=0; i < unique_values_in_column.get_y_dimension(); ++i){
                tree_node child(unique_values_in_column[i], max_index_profit_for_level_column, 1, Cnumpy::of(0));
                create_lower_level_tree(data, child, predict_column_index);
                node.add_child(child);
            }

            return node;
        }else{
            Cnumpy how_many_same_element_in_column = data.count(node.get_decision_index(),node.get_value());


            if(how_many_same_element_in_column.get_xy_int(0,0) == 1){


                Cnumpy one_rows_with_value = data.filter(node.get_decision_index(), node.get_value());
                tree_node child(node.get_value(), -1,node.get_level()+1, one_rows_with_value[predict_column_index]);

                node.set_label(one_rows_with_value[predict_column_index][0]);

                return child;
            }

            Cnumpy rows_with_same_value_in_column = data.filter(node.get_decision_index(), node.get_value());
            Cnumpy unique_labels_in_column = rows_with_same_value_in_column.get_unique_column_values(predict_column_index);

            if(unique_labels_in_column.get_y_dimension() == 1){


                node.set_label(rows_with_same_value_in_column[predict_column_index][0]);
                tree_node child(node.get_value(), -1,node.get_level()+1, rows_with_same_value_in_column[predict_column_index][0]);
                child.set_label(rows_with_same_value_in_column[predict_column_index][0]);
                node.set_label(rows_with_same_value_in_column[predict_column_index][0]);
                return child;

            }



            if(node.get_level() == (data.get_x_dimension()-1)){

                tree_node child(node.get_value(),-1,node.get_level()+1,Cnumpy::of("Brak"));

                return child;
            }

            Cnumpy filter_in_parent_column_predict = data.filter(node.get_decision_index(), node.get_value());
            Cnumpy unique_value = filter_in_parent_column_predict.get_unique_column_values(max_index_profit_for_level_column);


            Cnumpy   unique_data_in_actual_level = unique_value;


            for(int i=0; i < unique_data_in_actual_level.get_y_dimension(); ++i){


                tree_node child(unique_data_in_actual_level[i], max_index_profit_for_level_column, node.get_level() + 1, Cnumpy::of("BRAK!!!"));
                Cnumpy rows_with_same_value = data.filter(max_index_profit_for_level_column, unique_data_in_actual_level[i]);
                rows_with_same_value = rows_with_same_value.filter(node.get_decision_index(),node.get_value());

                create_lower_level_tree(rows_with_same_value, child, predict_column_index);

                node.add_child(child);

            }

            return  node;




        }









    }


    tree_node create_lower_level_tree_verbose(Cnumpy data, tree_node& node, int predict_column_index){

        std::cout<<"ZBIÓR DANYCH"<<std::endl;
        std::cout<<data<<std::endl;


        int number_column_max_profit_for_level = node.get_level();
        int max_index_profit_for_level_column = get_index_column_with_max_information_profit(data, number_column_max_profit_for_level, predict_column_index);

        std::cout<<"INDEX KOLUMNY Z MAKSYMALNYM ZYSKIEM INFORMACYJNYM DLA POZIOMU = "<<max_index_profit_for_level_column<<std::endl;
        std::cout<<"ELEMENT"<<std::endl;
        std::cout<<node.get_value()<<std::endl;


        if(node.is_root()){
            Cnumpy unique_values_in_column = data.get_unique_column_values(max_index_profit_for_level_column);

            std::cout<<"JESTEM KORZENIEM, UNIKALNE WARTOSĆI "<<std::endl;

            std::cout<<unique_values_in_column<<std::endl;

            for(int i=0; i < unique_values_in_column.get_y_dimension(); ++i){
                tree_node child(unique_values_in_column[i], max_index_profit_for_level_column, 1, Cnumpy::of(0));
                create_lower_level_tree_verbose(data, child, predict_column_index);
                node.add_child(child);
            }

            return node;
        }else{
            Cnumpy how_many_same_element_in_column = data.count(node.get_decision_index(),node.get_value());


            if(how_many_same_element_in_column.get_xy_int(0,0) == 1){

                std::cout<<"TYLKO JEDEN WIERSZ WYNIKOWY O TEJ WARTOŚĆI ETYKIETA"<<std::endl;


                Cnumpy one_rows_with_value = data.filter(node.get_decision_index(), node.get_value());
                tree_node child(node.get_value(), -1,node.get_level()+1, one_rows_with_value[predict_column_index]);

                std::cout<<one_rows_with_value[predict_column_index]<<std::endl;
                node.set_label(one_rows_with_value[predict_column_index][0]);

                return child;
            }

            Cnumpy rows_with_same_value_in_column = data.filter(node.get_decision_index(), node.get_value());
            Cnumpy unique_labels_in_column = rows_with_same_value_in_column.get_unique_column_values(predict_column_index);

            if(unique_labels_in_column.get_y_dimension() == 1){

                std::cout<<"WSZYSTKIE WIERSZE DAJA TA SAMA PREDYKCJE ETYKIETA TO"<< std::endl;
                node.set_label(rows_with_same_value_in_column[predict_column_index][0]);
                tree_node child(node.get_value(), -1,node.get_level()+1, rows_with_same_value_in_column[predict_column_index][0]);
                child.set_label(rows_with_same_value_in_column[predict_column_index][0]);
                std::cout<<rows_with_same_value_in_column[predict_column_index][0]<<std::endl;

                node.set_label(rows_with_same_value_in_column[predict_column_index][0]);

                return child;

            }


            std::cout<<node.get_level();
            std::cout<<data.get_y_dimension();

            if(node.get_level() == (data.get_x_dimension()-1)){
                std::cout<<"BRAK KOLUMN DO DALSZEJ PREDYKCJI BRAK WYNIKU"<<std::endl;
                tree_node child(node.get_value(),-1,node.get_level()+1,Cnumpy::of("Brak"));

                return child;
            }

            Cnumpy filter_in_parent_column_predict = data.filter(node.get_decision_index(), node.get_value());
            Cnumpy unique_value = filter_in_parent_column_predict.get_unique_column_values(max_index_profit_for_level_column);


            Cnumpy   unique_data_in_actual_level = unique_value;


            for(int i=0; i < unique_data_in_actual_level.get_y_dimension(); ++i){


                tree_node child(unique_data_in_actual_level[i], max_index_profit_for_level_column, node.get_level() + 1, Cnumpy::of("BRAK!!!"));


                Cnumpy rows_with_same_value = data.filter(max_index_profit_for_level_column, unique_data_in_actual_level[i]);
                rows_with_same_value = rows_with_same_value.filter(node.get_decision_index(),node.get_value());

                create_lower_level_tree_verbose(rows_with_same_value, child, predict_column_index);

                node.add_child(child);

            }

            return  node;




        }







    }


    tree_node construct_general_tree(Cnumpy data,int predict_column_index){
        tree_node* root = new tree_node;
        (*root).set_level(0);
        return create_lower_level_tree(data, (*root), predict_column_index);

    }


    tree_node construct_general_tree_verbose(Cnumpy data,int predict_column_index){
        tree_node* root = new tree_node;
        (*root).set_level(0);
        return create_lower_level_tree_verbose(data, (*root), predict_column_index);

    }



    Cnumpy predict(tree_node node, Cnumpy row_to_predict, int index = 0){


        std::vector<tree_node> children_elem_tree = node.get_children();


        if(node.is_leaf()){
            return node.get_label();
        }else {

            for (int i = 0; i < children_elem_tree.size(); ++i) {
                Cnumpy child = children_elem_tree[i].get_value();
                int decision_index = children_elem_tree[i].get_decision_index();
                Cnumpy value_in_decision_index_column = row_to_predict[decision_index];
                if (child == value_in_decision_index_column) {

                    return predict(children_elem_tree[i], row_to_predict, index + 1);

                }
            }

            return Cnumpy::of("BRAK");
        }

    }

    Cnumpy predict_verbose(tree_node node, Cnumpy row_to_predict, int index = 0){


        std::vector<tree_node> children_elem_tree = node.get_children();

        std::cout<<std::endl<<"ELEMENT "<<std::endl;
        std::cout<<node.get_value()<<std::endl;



        if(node.is_leaf()){
            std::cout<<"JESTEM LIŚĆIEM MOJA PREDYKCJA TO "<<std::endl;
            std::cout<<node.get_label()<<std::endl;
            return node.get_label();
        }else {

            std::cout<<"JESTEM WĘZŁEM MAM "<<children_elem_tree.size()<<" DZIECI "<<std::endl;
            for (int i = 0; i < children_elem_tree.size(); ++i) {
                Cnumpy child = children_elem_tree[i].get_value();
                int decision_index = children_elem_tree[i].get_decision_index();
                Cnumpy value_in_decision_index_column = row_to_predict[decision_index];



                if (child == value_in_decision_index_column) {
                    std::cout<<"ZNALAZŁEM PASUJĄCE DZIECKO"<<std::endl;
                    return predict_verbose(children_elem_tree[i], row_to_predict, index + 1);

                }
            }

            std::cout<<"BRAK PASUJĄCEGO ELEMENTU"<<std::endl;
            return Cnumpy::of("BRAK");
        }

    }


};


#endif //RANDOMFOREST_DECISION_TREE_H