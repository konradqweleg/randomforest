//
// Created by Konrad on 03.05.2023.
//

#include "Entropy.h"

#ifndef ENTROPY_H
#define ENTROPY_H




Cnumpy  Entropy::calculate_entropy_all_data_based_on_column(Cnumpy data, int index_column_determine_all_entropy_dataset){
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


Cnumpy  Entropy::calculate_information_profit_for_column(Cnumpy data, int column, int predict_column){
    Cnumpy predict_column_entropy = calculate_entropy_all_data_based_on_column(data, predict_column);
    Cnumpy values_entropy = calculate_entropy_for_columns(data, column, predict_column);
    return predict_column_entropy - values_entropy;
}


Cnumpy  Entropy::calculate_entropy_for_columns(Cnumpy data, int column_index, int predict_column_index){
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





#endif