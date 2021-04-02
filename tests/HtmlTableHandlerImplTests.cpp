#include "gtest/gtest.h"
#include "../Impl/HtmlTableHandlerImpl.h"

TEST (DefaultConstructor, SizeCheck) {
    HtmlTableHandlerImpl anImpl;
    EXPECT_EQ(std::get<0>(anImpl.getSize()), 0);
    EXPECT_EQ(std::get<1>(anImpl.getSize()), 0);
}

TEST (SizeConstructor, SizeCheck) {
    unsigned short int test_h=29999;
    unsigned short int test_w=27777;
    HtmlTableHandlerImpl anImpl(test_h, test_w);
    EXPECT_EQ(std::get<0>(anImpl.getSize()), test_h);
    EXPECT_EQ(std::get<1>(anImpl.getSize()), test_w);
}
