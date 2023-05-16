//
// Created by Konrad on 16.05.2023.
//

#ifndef RANDOMFOREST_HISTOGRAM_BASE_H
#define RANDOMFOREST_HISTOGRAM_BASE_H


#include "histogram.h"

class histogram_base : public histogram{
private:
    Cnumpy calculate_histogram_for_string(Cnumpy data,int column_index, double bins = 1.0);
    bool  is_allowed_1_bins_for_string_type_column(double bins);

public:
     virtual Cnumpy hist(Cnumpy data,int column_index, double bins = 1.0);

};


#endif //RANDOMFOREST_HISTOGRAM_BASE_H
