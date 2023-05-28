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
    #    RandomForest/Google_tests/quant_test.cpp
     #   RandomForest/Google_tests/cnumpy_test.cpp
        RandomForest/text/Text_operation.cpp RandomForest/text/Text_operation.h RandomForest/files/Files_utility.cpp RandomForest/files/Files_utility.h
       # RandomForest/Google_tests/text_operation_test.cpp
        RandomForest/csv/read_csv/ReadCSV.h RandomForest/csv/read_csv/ReadCSVBuffered.cpp RandomForest/csv/read_csv/ReadCSVBuffered.h RandomForest/csv/read_csv/ReadCSV_EachMethodOpenCloseFile.cpp RandomForest/csv/read_csv/ReadCSV_EachMethodOpenCloseFile.h RandomForest/entropy/Entropy.cpp RandomForest/entropy/Entropy.h RandomForest/Collection_Utility/Collection_Utility.h RandomForest/cnumpy/Exception_Cnumpy_Message.cpp RandomForest/cnumpy/Exception_Cnumpy_Message.h RandomForest/cnumpy/math/histogram.h RandomForest/cnumpy/math/histogram_base.cpp RandomForest/cnumpy/math/histogram_base.h RandomForest/quant/quant.cpp RandomForest/create_data_set.cpp RandomForest/create_data_set.h)

add_subdirectory(RandomForest/Google_tests) #