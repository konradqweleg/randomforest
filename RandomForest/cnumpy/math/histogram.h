//
// Created by Konrad on 16.05.2023.
//

#ifndef RANDOMFOREST_HISTOGRAM_H
#define RANDOMFOREST_HISTOGRAM_H
#include "../cnumpy.h"
#include <string>

class histogram{

public:
   static const std::string  FOR_STRING_ONLY_BINS_EQUALS_ONE_IS_ALLOWED;
   virtual ~histogram(){}
   virtual Cnumpy hist(Cnumpy data,int column_index, double bins = 1.0) = 0;
};

#endif //RANDOMFOREST_HISTOGRAM_H