//
// Created by Konrad on 03.05.2023.
//

#ifndef RANDOMFOREST_COLLECTION_UTILITY_H
#define RANDOMFOREST_COLLECTION_UTILITY_H
#include <vector>
#include <set>


static std::set<int> convertToSet(std::vector<int> v) {
    std::set<int> s(v.begin(), v.end());
    return s;
}












#endif //RANDOMFOREST_COLLECTION_UTILITY_H
