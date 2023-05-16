//
// Created by Konrad on 16.05.2023.
//

#include "histogram_base.h"
//czy to poprawne ?
const std::string  histogram::FOR_STRING_ONLY_BINS_EQUALS_ONE_IS_ALLOWED = "For text type only bins equal to one is acceptable";

Cnumpy histogram_base::hist(Cnumpy data,int column_index, double bins) {
    Type column_type = data.get_type_columns()[column_index];

    if(column_type == Type::string_type){
        return calculate_histogram_for_string(data,column_index,bins);
    }

}

Cnumpy histogram_base::calculate_histogram_for_string(Cnumpy data, int column_index, double bins) {

    if(!is_allowed_1_bins_for_string_type_column(bins)){
        throw std::invalid_argument(FOR_STRING_ONLY_BINS_EQUALS_ONE_IS_ALLOWED);
    }


        Cnumpy column_to_hist_values = (*this)[column_index];
        std::map<Cnumpy, int> histogram_values;


        for (int i = 0; i < column_to_hist_values.y_dimension; i++) {

            if (histogram_values.count(column_to_hist_values[i]) == 0) {
                histogram_values[column_to_hist_values[i]] = 1;
            } else {
                histogram_values[column_to_hist_values[i]] = histogram_values[column_to_hist_values[i]] + 1;
            }


        }


        std::vector<Type> type_column_histogram_cnumpy;
        type_column_histogram_cnumpy.push_back(column_type);
        type_column_histogram_cnumpy.push_back(Type::integer_type);

        std::vector<std::string> columns_name_histogram_cnumpy;
        columns_name_histogram_cnumpy.push_back("value");
        columns_name_histogram_cnumpy.push_back("quantity");


        std::vector<Cnumpy> key_hist_cnumpy;
        std::vector<int> value_count_cnumpy;

        for (const auto &entry: histogram_values) {
            key_hist_cnumpy.push_back(entry.first);
            value_count_cnumpy.push_back(entry.second);
        }

        Cnumpy results = Cnumpy(2, key_hist_cnumpy.size(), type_column_histogram_cnumpy, columns_name_histogram_cnumpy);
        results.set_column(0, key_hist_cnumpy);
        results.set_column(1, value_count_cnumpy);

        return results;





}

bool histogram_base::is_allowed_1_bins_for_string_type_column(double bins) {
    double  epsilon = 0.05;
    double allowed_value = 1.0;
    if (bins > (allowed_value+epsilon) || bins < (allowed_value-epsilon)) {
        return false;
    }
    return true;
}


/*
 *   Type column_type = type_column[column_index];


    if (column_type != Type::string_type) {
        Cnumpy step = Cnumpy::of(bins);
        if (column_type == Type::integer_type) {
            int bins_as_int = (int) bins;
            step = Cnumpy::of(bins_as_int);
        }

        Cnumpy min_value = get_min_value_in_column(column_index);
        Cnumpy max_value = get_max_value_in_column(column_index);


        Cnumpy column_to_hist_values = (*this)[column_index];
        std::map<Cnumpy, int> histogram_values;


        while (min_value < max_value) {
            if (histogram_values.count(min_value) == 0) {
                histogram_values[min_value] = 0;
            } else {
                histogram_values[min_value] = histogram_values[min_value] + 1;
            }

            min_value = min_value + step;

        }

        for (int i = 0; i < column_to_hist_values.y_dimension; i++) {
            Cnumpy elem = column_to_hist_values[i];
            Cnumpy bucket_for_element = elem / step;
            histogram_values[bucket_for_element] = histogram_values[bucket_for_element] + 1;

        }


        std::vector<Type> type_column_histogram_cnumpy;
        type_column_histogram_cnumpy.push_back(column_type);
        type_column_histogram_cnumpy.push_back(Type::integer_type);

        std::vector<std::string> columns_name_histogram_cnumpy;
        columns_name_histogram_cnumpy.push_back("value");
        columns_name_histogram_cnumpy.push_back("quantity");


        std::vector<Cnumpy> key_hist_cnumpy;
        std::vector<int> value_count_cnumpy;

        for (const auto &entry: histogram_values) {
            key_hist_cnumpy.push_back(entry.first);
            value_count_cnumpy.push_back(entry.second);
        }

        Cnumpy results = Cnumpy(2, key_hist_cnumpy.size(), type_column_histogram_cnumpy, columns_name_histogram_cnumpy);
        results.set_column(0, key_hist_cnumpy);
        results.set_column(1, value_count_cnumpy);
        return results;
    } else {


        if (bins > 1 || bins < 0.95) {
            throw std::invalid_argument("For text, the division index cannot be different from 1");
        }

        Cnumpy column_to_hist_values = (*this)[column_index];
        std::map<Cnumpy, int> histogram_values;


        for (int i = 0; i < column_to_hist_values.y_dimension; i++) {

            if (histogram_values.count(column_to_hist_values[i]) == 0) {
                histogram_values[column_to_hist_values[i]] = 1;
            } else {
                histogram_values[column_to_hist_values[i]] = histogram_values[column_to_hist_values[i]] + 1;
            }


        }


        std::vector<Type> type_column_histogram_cnumpy;
        type_column_histogram_cnumpy.push_back(column_type);
        type_column_histogram_cnumpy.push_back(Type::integer_type);

        std::vector<std::string> columns_name_histogram_cnumpy;
        columns_name_histogram_cnumpy.push_back("value");
        columns_name_histogram_cnumpy.push_back("quantity");


        std::vector<Cnumpy> key_hist_cnumpy;
        std::vector<int> value_count_cnumpy;

        for (const auto &entry: histogram_values) {
            key_hist_cnumpy.push_back(entry.first);
            value_count_cnumpy.push_back(entry.second);
        }

        Cnumpy results = Cnumpy(2, key_hist_cnumpy.size(), type_column_histogram_cnumpy, columns_name_histogram_cnumpy);
        results.set_column(0, key_hist_cnumpy);
        results.set_column(1, value_count_cnumpy);

        return results;


    }

 */