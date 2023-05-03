//
// Created by Konrad on 03.05.2023.
//

#ifndef RANDOMFOREST_ENTROPY_H
#define RANDOMFOREST_ENTROPY_H

#include <map>
#include "../cnumpy/cnumpy.h"
#include "../Collection_Utility/Collection_Utility.h"
#include <cmath>
class Entropy {


    std::map<int,int> how_many_count_value_first_value_second_count(Cnumpy data,int index_column_to_calculate_count_value){
        std::set<int> diffrent_value_in_determine_column = convertToSet(data.get_column_int(index_column_to_calculate_count_value));
        std::map<int, int> value_count_in_determine_column;

        for (int value: diffrent_value_in_determine_column) {
            for (int element_determine_column: data.get_column_int(index_column_to_calculate_count_value)) {
                if (value == element_determine_column) {
                    if (value_count_in_determine_column.count(value) == 0) {
                        value_count_in_determine_column[value] = 1;
                    } else {
                        value_count_in_determine_column[value] = value_count_in_determine_column[value] + 1;
                    }
                }
            }
        }

        return value_count_in_determine_column;
    }






public:
    double calculate_entropy_all_data_based_on_column(Cnumpy data,int index_column_determine_all_entropy){
        std::set<int> diffrent_value_in_determine_column = convertToSet(data.get_column_int(index_column_determine_all_entropy));
        std::map<int,int> count_value = how_many_count_value_first_value_second_count(data,index_column_determine_all_entropy);


   for(std::map<int,int>::iterator iter = count_value.begin(); iter != count_value.end(); ++iter)
    {
        int k =  iter->first;

        int v = iter->second;
        std::cout<<"Key = "<<k<<" Value = "<<v<<std::endl;
    }

   std::cout<<"y dim = "<<data.get_y_dimension()<<std::endl;

        double entropy = 0.0;
        for (int key: diffrent_value_in_determine_column) {
            entropy = entropy - (((double) count_value[key] / data.get_y_dimension()) *
                                 log2(((double) count_value[key] / data.get_y_dimension())));
        }

        return entropy;
    }
};


#endif //RANDOMFOREST_ENTROPY_H
