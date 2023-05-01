//
// Created by konra on 25.04.2023.
//

#include "gtest/gtest.h"
#include <string>
#include "../text/Text_operation.h"
#include "../text/Text_operation.cpp"
TEST(test_text_operation, remove_quote_from_text) {

    std::string text_with_quote = "\"text with quote\"";
    std::string results = Text_operation::remove_quote_from_string(text_with_quote);
    EXPECT_EQ("text with quote",results);

}

TEST(test_text_operation, split_text_by_delimiter) {

    std::string text_to_split = "text,split,via,delimiter";
    std::vector<std::string> results = Text_operation::split_by_delimiter(text_to_split, ",");

    EXPECT_EQ(4,results.size());
    EXPECT_EQ("text", results[0]);
    EXPECT_EQ("split", results[1]);
    EXPECT_EQ("via", results[2]);
    EXPECT_EQ("delimiter", results[3]);

}