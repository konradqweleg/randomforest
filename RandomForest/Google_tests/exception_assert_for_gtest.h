//
// Created by Konrad on 13.05.2023.
//

#ifndef RANDOMFOREST_EXCEPTION_ASSERT_FOR_GTEST_H
#define RANDOMFOREST_EXCEPTION_ASSERT_FOR_GTEST_H

#define ASSERT_EXCEPTION( TRY_BLOCK, EXCEPTION_TYPE, MESSAGE )        \
try                                                                   \
{                                                                     \
    TRY_BLOCK                                                         \
    FAIL() << "exception '" << MESSAGE << "' not thrown at all!";     \
}                                                                     \
catch( const EXCEPTION_TYPE& e )                                      \
{                                                                     \
    std::string actual_exception = e.what();                          \
    std::string expected_exception = MESSAGE;                         \
    EXPECT_EQ( expected_exception, actual_exception )                 \
        << " exception message is incorrect. Expected the following " \
           "message:\n\n"                                             \
        << MESSAGE << "\n"<<e.what();                                 \
}                                                                     \
catch( ... )                                                          \
{                                                                     \
    FAIL() << "exception '" << MESSAGE                                \
           << "' not thrown with expected type '" << #EXCEPTION_TYPE  \
           << "'!";                                                   \
}

#endif //RANDOMFOREST_EXCEPTION_ASSERT_FOR_GTEST_H
