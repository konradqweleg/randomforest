//
// Created by Konrad on 03.05.2023.
//

#ifndef RANDOMFOREST_COLLECTION_UTILITY_H
#define RANDOMFOREST_COLLECTION_UTILITY_H
#include <vector>
#include <set>


template<typename T> std::set<T> convertToSet(std::vector<T> v) {
    std::set<T> s(v.begin(), v.end());
    return s;
}


template<typename T> std::vector<T> convertToVector(std::set<T> v) {
    std::vector<T> s(v.begin(), v.end());
    return s;
}









#endif //RANDOMFOREST_COLLECTION_UTILITY_H
