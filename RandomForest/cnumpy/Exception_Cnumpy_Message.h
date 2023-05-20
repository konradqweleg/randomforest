//
// Created by Konrad on 15.05.2023.
//

#ifndef RANDOMFOREST_EXCEPTION_CNUMPY_MESSAGE_H
#define RANDOMFOREST_EXCEPTION_CNUMPY_MESSAGE_H

#include <string>
class Exception_Cnumpy_Message {
public:
     static std::string VALUE_TYPE_DO_NOT_MATCH ;
     static std::string OPERATION_ALLOWED_FOR_ONE_ELEMENT_CNUMPY;
     static std::string BOTH_DIMENSION_MUST_BE_ABOVE_ZERO;
     static std::string ACCESS_INDEX_MUST_BE_GREATER_OR_EQUAL_ZERO;
     static std::string INDEXES_MUST_BE_SMALLER_THAN_DIMENSION_OF_CNUMPY;
     static std::string TEXT_SUBTRACTION_OPERATION_IS_NOT_ALLOWED;
     static std::string TEXT_DIVIDE_OPERATION_IS_NOT_ALLOWED;
     static std::string TEXT_MULTIPLICATION_IS_NOT_ALLOWED;
     static std::string TEXT_NEGATION_IS_NOT_ALLOWED;
     static std::string OPERATION_ALLOWED_ONLY_FOR_SAME_MATRIX_DIMENSIONS;
     static std::string NULL_POINTER_STRATEGY;


};



#endif //RANDOMFOREST_EXCEPTION_CNUMPY_MESSAGE_H
