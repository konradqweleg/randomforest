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

class decision_tree {


    tree_node construct_general_tree();


    static std::vector<double> quant_column(std::vector<double> data, int groups) {
        std::vector<int> result;

        double min_value = *min_element(std::begin(data), std::end(data));
        double max_value = *max_element(std::begin(data), std::end(data));

        //std::cout<<"Min : "<<min_value<<std::endl;
        // std::cout<<"Max : "<<max_value<<std::endl;

        double diff_min_max = max_value - min_value;
        double step = diff_min_max / groups;
        double threshold = min_value + step;
        std::cout << "krok : " << step << std::endl;

        for (int i = 0; i < groups; i++) {
            std::cout << "Prog = " << threshold << " index = " << i << std::endl;
            for (double a: data) {
                if (a < threshold && a > threshold - step) {
                    std::cout << a << " ";
                    result.push_back(i);
                }
            }
            threshold += step;
            std::cout << std::endl;
        }


        std::cout << "Skwantowane dane " << std::endl;

        for (auto ww: result) {
            std::cout << ww << std::endl;
        }

    }

public:

    static std::set<int> convertToSet(std::vector<int> v) {
        std::set<int> s(v.begin(), v.end());
        return s;
    }

    static double entropy_result(std::vector<int> results) {
        std::set<int> diffrent_value_in_result = convertToSet(results);
        std::map<int, int> how_many_result_in_result;
        double entropy = 0;

        for (int value: diffrent_value_in_result) {
            for (int x: results) {
                if (value == x) {
                    if (how_many_result_in_result.count(value) == 0) {
                        how_many_result_in_result[value] = 1;
                    } else {
                        how_many_result_in_result[value] = how_many_result_in_result[value] + 1;
                    }
                }
            }
        }

        for (int key: diffrent_value_in_result) {
            entropy = entropy - (((double) how_many_result_in_result[key] / results.size()) *
                                 log2(((double) how_many_result_in_result[key] / results.size())));
        }
        return entropy;

    }


    static std::map<int, int> how_many_key_in_results(std::vector<int> values) {
        std::map<int, int> how_many_key_in_result;


        for (int a: values) {
            if (how_many_key_in_result.count(a) == 0) {
                how_many_key_in_result[a] = 0;
            }


        }


        for (int value: values) {


          //  for (int i = 0; i < values.size(); ++i) {
             //   if (values[i] == value) {
                    how_many_key_in_result[value] = how_many_key_in_result[value] + 1;
              //  }
          //  }

        }

        return how_many_key_in_result;
    }

    static std::map<int, double> entropy_for_column(std::vector<int> data, std::vector<int> results) {

        std::set<int> diffrent_value_in_column = convertToSet(data);
        std::map<int, int> how_many_key_in_result;
        std::map<int, double> entropy;


        for (int value: diffrent_value_in_column) {

            for (int a: results) {
                if (how_many_key_in_result.count(a) == 0) {
                    how_many_key_in_result[a] = 0;
                }


            }

            int size_data = 0;
            for (int i = 0; i < results.size(); ++i) {
                if (data[i] == value) {
                    size_data++;
                    how_many_key_in_result[results[i]] = how_many_key_in_result[results[i]] + 1;
                }
            }


            entropy[value] = 0.0;
            for (int key: diffrent_value_in_column) {
                std::cout << key << " , " << how_many_key_in_result[key] << " rozmiar " << size_data << std::endl;

                // std::cout<<(double) how_many_key_in_result[key] / size_data<<" * "<<log2(((double) how_many_key_in_result[key] / size_data))<<" ";
                std::cout << std::endl;

                if (how_many_key_in_result[key] == 0) {

                } else {
                    entropy[value] = entropy[value] - (((double) how_many_key_in_result[key] / size_data) *
                                                       log2(((double) how_many_key_in_result[key] / size_data)));
                }
            }


            how_many_key_in_result = std::map<int, int>();

        }

        return entropy;


    }


    static double get_information_profit(std::map<int,double> entropy_column, std::vector<int> values, std::vector<int> result) {

        std::map<int,int> how_many_key = how_many_key_in_results(values);
        std::map<int,int> keys = how_many_key_in_results(result);
        double entropy_criteria = entropy_result(result);

        double sum_mean = 0.0;


        for(std::map<int,int>::iterator iter = how_many_key.begin(); iter != how_many_key.end(); ++iter)
        {

            sum_mean += (((double)(iter ->second))/result.size()) * entropy_column[iter -> first];

        }


        return entropy_criteria - sum_mean;

    }


    static Cnumpy quant_data(Cnumpy data, double percentage, std::string label) {
        int quantity_group = 1.0 / percentage;
        std::cout << quantity_group << std::endl;

        for (int x = 0; x < data.get_x_dimension(); x++) {

            if (data.get_column_name()[x] == label) {
                continue;
            }

            if (data.get_type_column()[x] == Type::double_type) {
                std::vector<double> column = data.get_column<double>(x);
                column = quant_column(column, quantity_group);

            }

        }

        return data;
    }


};


#endif //RANDOMFOREST_DECISION_TREE_H
