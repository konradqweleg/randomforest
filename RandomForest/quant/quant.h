//
// Created by Konrad on 18.04.2023.
//

#ifndef RANDOMFOREST_QUANT_H
#define RANDOMFOREST_QUANT_H

#include <vector>
#include <string>
#include "../cnumpy/cnumpy.h"
#include <algorithm>
#include <iostream>
#include <numeric>


class quant_utility {
//More flexibility is provided by the implementation for individual columns. Code to delete
    /*
    static Cnumpy quant_data_in_cnumpy(Cnumpy data, double percentage_group_in_split, int predict_column_index) {

        double hundred_percentage = 1.0;
        int quantity_group = hundred_percentage / percentage_group_in_split;

        for (int column_index = 0; column_index < data.get_x_dimension(); column_index++) {

            if (column_index == predict_column_index) {
                continue;
            }

            if (data.get_type_column()[column_index] == Type::double_type) {
                std::vector<double> column = data.get_column<double>(column_index);
                column = quant_column_double_to_int(column, quantity_group);

            }

        }

        return data;
    }
*/

public:

    //this is only my method so is no quite optimal for example, parametrized is good option
    static std::vector<double> quant_column_double_betweeen_method_result_avg_group(std::vector<double> column_data, double percentage_group_in_split) {
        double hundred_percentage = 1.0;
        int how_many_groups = hundred_percentage / percentage_group_in_split;

        std::vector<double> result;

        double min_value = *min_element(std::begin(column_data), std::end(column_data));
        double max_value = *max_element(std::begin(column_data), std::end(column_data));

        double diff_min_max = max_value - min_value;
        double step = diff_min_max / how_many_groups;
        double threshold = min_value + step;


        for (int i = 0; i < how_many_groups; i++) {

            for (double value: column_data) {
                if (value < threshold && value > threshold - step) {


                    double department_range_avg = threshold + (threshold - (threshold-step))/2;
                    result.push_back(  department_range_avg);
                    std::cout<<" Th: "<<threshold<<"  "<<department_range_avg<<std::endl;
                }
            }
            threshold += step;

        }

        return result;
    }





};

#endif //RANDOMFOREST_QUANT_H
