//
// Created by Konrad on 16.05.2023.
//

#include "histogram_base.h"


Cnumpy histogram_base::hist(Cnumpy data, int column_index) {

    Cnumpy unique_values_hist_key = data.get_unique_column_values(column_index);

    std::vector<Type> type_columns_hist{data.get_type_columns()[column_index], Type::integer_type};
    std::vector<std::string> description_columns{"key","values"};

    Cnumpy hist_data = Cnumpy(2, unique_values_hist_key.get_y_dimension(), type_columns_hist, description_columns);

    for (int i = 0; i < unique_values_hist_key.get_y_dimension(); i++) {
        int quantity = data[column_index].count(0, unique_values_hist_key[i]);
        hist_data.set(0, i, unique_values_hist_key[i]);
        hist_data.set(1, i, quantity);
    }

  return hist_data;
}

