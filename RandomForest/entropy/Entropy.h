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


    std::map<int, int> calculate_histogram_for_column(Cnumpy data, int index_column_to_calculate_count_value) {
        std::set<int> diffrent_value_in_determine_column = convertToSet(
                data.get_column_int(index_column_to_calculate_count_value));
        std::vector<int> determine_column = data.get_column_int(index_column_to_calculate_count_value);
        std::map<int, int> value_count_in_determine_column;

        for (int value: diffrent_value_in_determine_column) {
            for (int element_determine_column: determine_column) {
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
    double calculate_entropy_all_data_based_on_column(Cnumpy data, int index_column_determine_all_entropy) {
        std::set<int> diffrent_value_in_determine_column = convertToSet(data.get_column_int(index_column_determine_all_entropy));
        std::map<int, int> histogram_determine_column = calculate_histogram_for_column(data, index_column_determine_all_entropy);

        double entropy = 0.0;
        for (int key: diffrent_value_in_determine_column) {
            entropy = entropy - (((double) histogram_determine_column[key] / data.get_y_dimension()) *
                                 log2(((double) histogram_determine_column[key] / data.get_y_dimension())));
        }
        return entropy;
    }

    Cnumpy CNUMPY_calculate_entropy_all_data_based_on_column(Cnumpy data,int index_column_determine_all_entropy_dataset){
        Cnumpy histogram_determine_column = data.hist(index_column_determine_all_entropy_dataset);
        Cnumpy entropy = Cnumpy::of(0.0);

        for(int i=0;i<histogram_determine_column.get_y_dimension();++i){
            Cnumpy percentage_quantity_in_all_data_values = Cnumpy::of(((double)histogram_determine_column[1][i].get_xy_int(0,0)) / (data.get_y_dimension()));
            Cnumpy log_percentage_quantity_in_all_values =  Cnumpy::of( log2(percentage_quantity_in_all_data_values.get_xy_double(0,0)));
            Cnumpy entropy_one_value = percentage_quantity_in_all_data_values * log_percentage_quantity_in_all_values;
            entropy-=entropy_one_value;
        }

        return entropy;
    }


    Cnumpy CNUMPY_calculate_information_profit_for_column(Cnumpy data,int column,int predict_column){
        Cnumpy predict_column_entropy = CNUMPY_calculate_entropy_all_data_based_on_column(data,predict_column);
        Cnumpy values_entropy = CNUMPY_calculate_entropy_for_columns(data,column,predict_column);
        return predict_column_entropy - values_entropy;
    }


    Cnumpy CNUMPY_calculate_entropy_for_columns(Cnumpy data, int column_index, int predict_column_index){
        Cnumpy unique_values = data.get_unique_column_values(column_index);


        Cnumpy final_result = Cnumpy::of(0.0);

        for(int i=0;i<unique_values.get_y_dimension();++i) {

            Cnumpy one_value_rows = data.filter(column_index, unique_values[i]);
            Cnumpy hist_predict_values_in_one_value = one_value_rows.hist(predict_column_index);
            Cnumpy value_entropy = Cnumpy::of(0.0);
            for(int j=0; j < hist_predict_values_in_one_value.get_y_dimension(); ++j){

                Cnumpy value_entropy_calc   = ((double) hist_predict_values_in_one_value[1][j].get_xy_int(0, 0) / (double) (one_value_rows.get_y_dimension())         ) * log2((double) hist_predict_values_in_one_value[1][j].get_xy_int(0, 0) / (double) (one_value_rows.get_y_dimension())    );
                value_entropy -= value_entropy_calc;

            }

            Cnumpy count_value_in_all_columns = data.count(column_index, unique_values[i]);

            Cnumpy attribute_entropy = Cnumpy::of(((double)count_value_in_all_columns.get_xy_int(0, 0) / (double) data.get_y_dimension()) * value_entropy.get_xy_double(0, 0));

            final_result +=  attribute_entropy;


        }



        return final_result;
    }




    std::map<int, int> histogram_value_in_predict_column(int value,Cnumpy data,int column_index,int predict_column_index){
        std::vector<int> column_value = data.get_column_int(column_index);
        std::vector<int> predict_column = data.get_column_int(predict_column_index);
        std::map<int, int> hist;
        for (int i = 0; i < column_value.size(); ++i) {
            if (value == column_value[i]) {
                if (hist.count(predict_column[i]) == 0) {
                    hist[predict_column[i]] = 1;
                } else {
                    hist[predict_column[i]] = hist[predict_column[i]] + 1;
                }
            }

        }

        return hist;

    }


    double calculate_information_gain_for_column(Cnumpy data, int column, int predict_column_index) {
        std::set<int> diffrent_value_in_column = convertToSet(data.get_column_int(column));
        std::vector<int> columns_values = data.get_column_int(column);
        std::vector<int> predict_column = data.get_column_int(predict_column_index);



        double information_gain = calculate_entropy_all_data_based_on_column(data, 2);




        for (auto value_in_column: diffrent_value_in_column) {


            std::map<int, int> how_key_value = histogram_value_in_predict_column(value_in_column,data,0,2);





            int total_sum = std::accumulate(how_key_value.begin(), how_key_value.end(), 0,
                                            [](auto prev_sum, auto &entry) {
                                                return prev_sum + entry.second;
                                            });

            double entropy = 0.0;


            for (auto iter = how_key_value.begin(); iter != how_key_value.end(); ++iter) {
                entropy = entropy - ((iter->second / (double) total_sum) * log2(iter->second / (double) total_sum));

            }

            information_gain = information_gain - (((double) total_sum / predict_column.size()) * entropy);

        }

        return information_gain;

    }
};


#endif //RANDOMFOREST_ENTROPY_H
