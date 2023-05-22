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

public:

    static Cnumpy quant_column_double_betweeen_method_result_avg_group(Cnumpy data,int column_index, int how_many_groups) {

        std::vector<double> result;

        double min_value = data.get_min_value_in_column(column_index).get_xy_double(0,0);
        double max_value = data.get_max_value_in_column(column_index).get_xy_double(0,0);

        double diff_min_max = max_value - min_value;
        double step = diff_min_max / how_many_groups;



        double min_ =0.0;
        double max_ =1.0;

        for (double value: data.get_column_double(column_index)) {
            double depart = (value-min_value) / ((double)step);

                for(int i =0;i<how_many_groups;++i){
                    if( depart >= min_ && depart < max_ ){

                        double department_range_avg =  (step * (i+1));
                        result.push_back(department_range_avg);

                        break;
                    }

                    if(i == (how_many_groups-1)){

                        double department_range_avg =  (step * (i+1));
                        result.push_back(department_range_avg);
                    }
                    min_ +=1.0;
                    max_+=1.0;
                }
                min_ =0.0;
                max_ =1.0;


        }


        return Cnumpy::of(result);
    }






};

#endif //RANDOMFOREST_QUANT_H
