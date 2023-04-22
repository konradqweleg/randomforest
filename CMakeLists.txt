cmake_minimum_required(VERSION 3.20)
project(randomforest)

set(CMAKE_CXX_STANDARD 14)

include_directories(RandomForest)

add_executable(randomforest
        RandomForest/cnumpy/cnumpy.cpp
        RandomForest/cnumpy/cnumpy.h
        RandomForest/csv/csv.cpp
        RandomForest/csv/csv.h
        RandomForest/main.cpp
        RandomForest/type.h
        RandomForest/decision_tree/decision_tree.h
        RandomForest/decision_tree/tree_node.h
        RandomForest/Google_tests/quant_test.cpp #
        RandomForest/Google_tests/cnumpy_test.cpp)

add_subdirectory(RandomForest/Google_tests) #