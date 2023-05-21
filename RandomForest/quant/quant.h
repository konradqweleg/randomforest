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

            if (data.get_type_columns()[column_index] == Type::double_type) {
                std::vector<double> column = data.get_column_double<double>(column_index);
                column = quant_column_double_to_int(column, quantity_group);

            }

        }

        return data;
    }
*/

public:

    //this is only my method so is no quite optimal for example, parametrized is good option
    static Cnumpy quant_column_double_betweeen_method_result_avg_group(Cnumpy data,int column_index, int how_many_groups) {

        std::vector<double> result;

        double min_value = data.get_min_value_in_column(column_index).get_xy_double(0,0);
        double max_value = data.get_max_value_in_column(column_index).get_xy_double(0,0);

        double diff_min_max = max_value - min_value;
        double step = diff_min_max / how_many_groups;
        double threshold = min_value + step;

        std::cout<<diff_min_max<<std::endl;
        std::cout<<step<<std::endl;
        std::cout<<threshold<<std::endl;

        double min_ =0.0;
        double max_ =1.0;

        for (double value: data.get_column_double(column_index)) {
            double depart = (value-min_value) / ((double)step);
                std::cout<<"Przedzial : "<<depart<<std::endl;

                for(int i =0;i<how_many_groups;++i){
                    if( depart >= min_ && depart < max_ ){

                        double department_range_avg =  (step * (i+1));
                        std::cout<<"Prognoza "<<i<< " Wartosc:"<<department_range_avg<<std::endl;
                        result.push_back(department_range_avg);

                        break;
                    }

                    if(i == (how_many_groups-1)){

                        double department_range_avg =  (step * (i+1));
                        result.push_back(department_range_avg);
                        std::cout<<"Prognoza "<<i<< " Wartosc:"<<department_range_avg<<std::endl;
                    }
                    min_ +=1.0;
                    max_+=1.0;
                }
                min_ =0.0;
                max_ =1.0;


        }

//        for (int i = 0; i < how_many_groups; i++) {
//
//            for (double value: data.get_column_double(column_index)) {
//                if (value < threshold && value > threshold - step) {
//
//                    double department_range_avg = threshold + (threshold - (threshold-step))/2;
//                    result.push_back(  department_range_avg);
//                }
//            }
//            threshold += step;
//
//        }

        return Cnumpy::of(result);
    }


    static Cnumpy CNUMPY_quant_column_double_betweeen_method_result_avg_group(Cnumpy data,int index_column, int how_groups) {
        std::cout<<":D";
        Cnumpy how_many_groups = Cnumpy::of(how_groups);

        Cnumpy result = data[index_column];

        Cnumpy min_value = data.get_min_value_in_column(index_column);
        Cnumpy max_value = data.get_max_value_in_column(index_column);

        Cnumpy diff_min_max = max_value - min_value;
        Cnumpy step = diff_min_max / how_many_groups;
        Cnumpy threshold = min_value + step;

        std::cout<<diff_min_max;
        std::cout<<step;
        std::cout<<threshold;
        for (Cnumpy i = 0; i < how_many_groups; ) {

            for (int j=0;j<data.get_y_dimension();++j) {
                Cnumpy value = data[index_column][j];
                Cnumpy lower_band = threshold - step;
                if ( (value < threshold) && (value > lower_band)) {

                    Cnumpy lower = threshold-step;
                    Cnumpy right_band = (threshold - lower);
                    Cnumpy two = Cnumpy::of(2.0);
                    Cnumpy avg_threshold = right_band/two;
                    Cnumpy department_range_avg = threshold + right_band;
                    result.set(j,department_range_avg);
                    std::cout<<" Th: "<<threshold<<"  "<<department_range_avg<<std::endl;
                }
            }
            threshold += step;


            Cnumpy one = Cnumpy::of(1);
            i +=one;
        }

        return result;
    }




};

#endif //RANDOMFOREST_QUANT_H
