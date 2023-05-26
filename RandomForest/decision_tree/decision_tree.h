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

    int get_index_column_with_max_information_profit(Cnumpy data,int wchich_number,int predict_column){
        histogram* hist_strategy = new histogram_base();
        Cnumpy::set_histogram_calculation_strategy(hist_strategy);
        Entropy entropy_strategy;
        csv csv_reader;

        std::map<int,double> entropy_value;

        for(int i=0;i<data.get_x_dimension();++i){
            if(i==predict_column){
                continue;
            }
            Cnumpy entropy_columns = entropy_strategy.calculate_information_profit_for_column(data, i, predict_column);

            entropy_value[i] = entropy_columns.get_xy_double(0,0);



        }


        std::vector<std::pair<int, double>> sVector;
        for(auto m: entropy_value){
            sVector.push_back(std::make_pair(m.first, m.second));
        }


        sort(sVector.begin(), sVector.end(), sortByVal);

        return sVector[wchich_number].first;

    }


    int ileRazy = 0;

    tree_node create_lvl_below(Cnumpy data,tree_node& node,int predict_column_index){

        ileRazy++;
        std::cout<<"Ile razy wywołuje "<<ileRazy<<" pcindex"<<predict_column_index<<std::endl;
        std::cout<<data;
        int number_max_profit_for_level = node.get_level();
        int max_index_profit_for_level_column = get_index_column_with_max_information_profit(data, number_max_profit_for_level, predict_column_index);

        if(node.is_root()){
            Cnumpy unique_value = data.get_unique_column_values(max_index_profit_for_level_column);
            std::cout<<"Korzen "<<std::endl;
            std::cout<<unique_value;

            for(int i=0;i<unique_value.get_y_dimension();++i){
                tree_node child(unique_value[i],max_index_profit_for_level_column,1,Cnumpy::of(0));
                std::cout<<" Dzieci korzenia "<<child.get_name()<<std::endl;
                create_lvl_below(data,child,predict_column_index);
                node.add_child(child);

            }

            return node;

            std::cout<<std::endl<<std::endl;

        }else{
            Cnumpy how_many_same_element_in_column = data.count(node.get_decision_index(),node.get_value());
            std::cout<<node.get_value()<<std::endl;
            std::cout<<"Ilość wystąpień tej wartośći to : "<<how_many_same_element_in_column.get_xy_int(0,0)<<" w kolumnie "<<node.get_decision_index();


            if(how_many_same_element_in_column.get_xy_int(0,0) == 1){

                std::cout<<"Jedna taka wartosć w zbiorze"<<std::endl;
                Cnumpy label_final = data.filter(node.get_decision_index(),node.get_value());
                label_final = label_final[predict_column_index];
                std::cout<<std::endl;
                std::cout<<label_final;
                std::cout<<std::endl;
                std::cout<<"PROGNOZA ::1 ="<<std::endl<<label_final<<std::endl;
                tree_node child(node.get_value(),-1,node.get_level()+1,label_final);
                std::cout<<child.get_name();
                return child;
            }

            Cnumpy filtered = data.filter(node.get_decision_index(),node.get_value());
            std::cout<<"filtered"<<std::endl;
            std::cout<<filtered;
            Cnumpy unique_labels = filtered.get_unique_column_values(predict_column_index);


            std::cout<<"y dim = "<<unique_labels.get_y_dimension()<<"index max predict"<<max_index_profit_for_level_column<<"predict"<<predict_column_index<<std::endl;
            std::cout<<"WARTOŚĆI"<<std::endl;
            std::cout<<unique_labels;
            std::cout<<std::endl;
            if(unique_labels.get_y_dimension() == 1){
                std::cout<<"Wszystkie predykcje dla wartości takie same"<<std::endl;
                std::cout<<"PROGNOZA ::2 ="<<std::endl<<filtered[predict_column_index][0]<<std::endl;
                tree_node child(node.get_value(),-1,node.get_level()+1,filtered[predict_column_index][0]);
                std::cout<<child.get_name();
                return child;

            }

            if(node.get_level() == (data.get_x_dimension()-1)){
                std::cout<<"Koniec kolumn do predykcji"<<std::endl;
                std::cout<<"PROGNOZA ::3 BRAK;"<<std::endl;

                tree_node child(node.get_value(),-1,node.get_level()+1,Cnumpy::of("Brak"));
                std::cout<<child.get_name();
                return child;
            }





            std::cout<<"Tworze dzieci bo mogę :Dxd "<<std::endl;
            std::cout<<data;
            Cnumpy unique_value = data.get_unique_column_values(max_index_profit_for_level_column);
            std::cout<<"Tworze dzieci bo mogę :D "<<std::endl;
            std::cout<<unique_value;
            for(int i=0;i<unique_value.get_y_dimension();++i){

                std::cout<<"--> "<<std::endl<<unique_value[i]<<std::endl;
                tree_node child(unique_value[i],max_index_profit_for_level_column,node.get_level()+1,Cnumpy::of(0));
                  std::cout<<" Dziecko "<<child.get_name()<<std::endl;
                  std::cout<<data;
                  std::cout<<node.get_value();
                Cnumpy data_ft = data.filter(max_index_profit_for_level_column,unique_value[i]);
                std::cout<<"ft"<<std::endl;
                create_lvl_below(data_ft,child,predict_column_index);
                node.add_child(child);

            }

            return  node;




        }







    }


    tree_node construct_general_tree(Cnumpy data,int predict_column_index){
        tree_node* root = new tree_node;
        (*root).set_level(0);
        int column_with_max_information_profit = get_index_column_with_max_information_profit(data,0,predict_column_index);
        return create_lvl_below(data,(*root),predict_column_index);

    }



    Cnumpy returnReturnLabel(tree_node node,Cnumpy row,int index =0){
        std::cout << "Przechodze!!!";
        std::cout<<"Elem:"<<node.get_value()<<" , "<<node.get_label();
        std::vector<tree_node> children = node.get_children();

        if(node.is_leaf()){
            std::cout << "JEstem lisciem moja etykieta to";
            std::cout<<node.get_label();
            return node.get_label();
        }else {

            for (int i = 0; i < children.size(); ++i) {
                Cnumpy child = children[i].get_value();
                Cnumpy i_am = row[index];

                if (child == i_am) {
                    std::cout << "Przechodze";

                    std::cout << children[i].get_label();
                  return  returnReturnLabel(children[i],row,index+1);

                }
            }
        }



    }








};


#endif //RANDOMFOREST_DECISION_TREE_H
