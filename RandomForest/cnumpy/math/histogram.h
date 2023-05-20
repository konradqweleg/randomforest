//
// Created by Konrad on 16.05.2023.
//



#ifndef RANDOMFOREST_HISTOGRAM_H
#define RANDOMFOREST_HISTOGRAM_H
#pragma once
#include <string>
#include "../cnumpy.h"



class histogram{

public:
   static const std::string  FOR_STRING_ONLY_BINS_EQUALS_ONE_IS_ALLOWED;
   virtual ~histogram(){}
   virtual Cnumpy hist(Cnumpy data,int column_index = 0)=0;
};


#endif //RANDOMFOREST_HISTOGRAM_H