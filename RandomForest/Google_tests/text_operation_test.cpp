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