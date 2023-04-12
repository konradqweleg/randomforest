cmake_minimum_required(VERSION 3.25)
project(randomforest)

set(CMAKE_CXX_STANDARD 14)

include_directories(RandomForest)

add_executable(randomforest
        RandomForest/cnumpy.cpp
        RandomForest/cnumpy.h
        RandomForest/csv.cpp
        RandomForest/csv.h
        RandomForest/main.cpp
        RandomForest/type.h)
