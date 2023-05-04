//
// Created by Konrad on 03.05.2023.
//

#ifndef RANDOMFOREST_ENTROPY_H
#define RANDOMFOREST_ENTROPY_H

#include <map>
#include "../cnumpy/cnumpy.h"
#include "../Collection_Utility/Collection_Utility.h"
#include <cmath>
#include <numeric>
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


//   for(std::map<int,int>::iterator iter = count_value.begin(); iter != count_value.end(); ++iter)
//    {
//        int k =  iter->first;
//
//        int v = iter->second;
//        std::cout<<"Key = "<<k<<" Value = "<<v<<std::endl;
//    }

   std::cout<<"y dim = "<<data.get_y_dimension()<<std::endl;

        double entropy = 0.0;
        for (int key: diffrent_value_in_determine_column) {
            entropy = entropy - (((double) count_value[key] / data.get_y_dimension()) *
                                 log2(((double) count_value[key] / data.get_y_dimension())));
        }

        return entropy;
    }


    double calculate_entropy_for_column(Cnumpy data,int column,int predict_column_index){
        std::set<int> diffrent_value_in_column = convertToSet(data.get_column_int(column));
        std::vector<int> all_value_in_column = data.get_column_int(column);
        std::vector<int> predict_column = data.get_column_int(predict_column_index);


        double information_gain = calculate_entropy_all_data_based_on_column(data,2);

        for(auto value_in_column : diffrent_value_in_column){

            std::map<int,int> how_key_value;
            for(int i=0;i<all_value_in_column.size();++i){
                if(value_in_column == all_value_in_column[i]) {
                    if (how_key_value.count(predict_column[i]) == 0) {
                        how_key_value[predict_column[i]] = 1;
                    }else{
                        how_key_value[predict_column[i]] = how_key_value[predict_column[i]] +1;
                    }
                }

            }

            std::cout<<"-----------------------"<<std::endl;
            std::cout<<std::endl;
            for(std::map<int,int>::iterator iter = how_key_value.begin(); iter != how_key_value.end(); ++iter)
            {
                int k =  iter->first;

                int v = iter->second;
                std::cout<<"Key = "<<k<<" Value = "<<v<<std::endl;
            }


            int total_sum = std::accumulate(how_key_value.begin(), how_key_value.end(), 0,
                                            [](auto prev_sum, auto &entry) {
                                                return prev_sum + entry.second;
                                            });

            double entropy = 0.0;


            for(std::map<int,int>::iterator iter = how_key_value.begin(); iter != how_key_value.end(); ++iter)
            {
                int k =  iter->first;

                int v = iter->second;
                entropy = entropy - ((iter->second/(double)total_sum) * log2(iter->second/(double)total_sum));


            }

            information_gain = information_gain - (((double )total_sum/predict_column.size())*entropy);

            std::cout<<"Entropy : "<<entropy<<std::endl;
            std::cout<<"-----------------------"<<std::endl;
            std::cout<<std::endl;

        }

        std::cout<<"IG: "<<information_gain<<std::endl;

    }
};


#endif //RANDOMFOREST_ENTROPY_H
