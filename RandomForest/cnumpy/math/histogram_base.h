//
// Created by Konrad on 16.05.2023.
//

#ifndef RANDOMFOREST_HISTOGRAM_BASE_H
#define RANDOMFOREST_HISTOGRAM_BASE_H


#include "histogram.h"
#include "../cnumpy.h"

class histogram_base : public histogram{
public:
     virtual Cnumpy hist(Cnumpy data,int column_index);
     virtual ~histogram_base(){};
     histogram_base(){};

};


#endif //RANDOMFOREST_HISTOGRAM_BASE_H
