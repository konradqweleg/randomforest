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

public:


    Cnumpy calculate_entropy_all_data_based_on_column(Cnumpy data, int index_column_determine_all_entropy_dataset);


    Cnumpy calculate_information_profit_for_column(Cnumpy data, int column, int predict_column);


    Cnumpy calculate_entropy_for_columns(Cnumpy data, int column_index, int predict_column_index);


};


#endif //RANDOMFOREST_ENTROPY_H
