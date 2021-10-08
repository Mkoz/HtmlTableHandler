#include "gtest/gtest.h"
#include "../Impl/HtmlTableHandlerImpl.h"
#include "../Impl/HTHConst.h"



TEST (DefaultConstructor, ConsisntecyCheck) {
    HtmlTableHandlerImpl anImpl;
    EXPECT_EQ(std::get<0>(anImpl.getSize()), 0);
    EXPECT_EQ(std::get<1>(anImpl.getSize()), 0);
    EXPECT_EQ(anImpl.getHeader().Name() , HTH_DEFAULT_TABLE_NAME);
}

TEST (SizeConstructor, ConsisntecyCheck) {
    unsigned short int test_h=29999;
    unsigned short int test_w=27777;
    HtmlTableHandlerImpl anImpl(test_h, test_w);
    EXPECT_EQ(std::get<0>(anImpl.getSize()), test_h);
    EXPECT_EQ(std::get<1>(anImpl.getSize()), test_w);
    EXPECT_EQ(anImpl.getHeader().Name() , HTH_DEFAULT_TABLE_NAME);
}

TEST (Header, Set_ConsisntecyCheck_InitilyzerList) {
    unsigned short int test_h=29999;
    unsigned short int test_w=27777;
    HtmlTableHandlerImpl anImpl(test_h, test_w);
    //Create empty initializer list
    auto aList = {"H1", "H2", "H3", "H4", "H5"};
    anImpl.setHeader(aList);
    EXPECT_EQ(anImpl.getHeader().Name() , HTH_DEFAULT_TABLE_NAME);
    EXPECT_EQ(std::string("<HTH_Table><th>H1</th><th>H2</th><th>H3</th><th>H4</th><th>H5</th></HTH_Table>"), anImpl.getHeader().ToString());

    aList = {"H6", "H7", "H8", "H9", "H10"};
    anImpl.setHeader(aList);
    EXPECT_EQ(anImpl.getHeader().Name() , HTH_DEFAULT_TABLE_NAME);
    EXPECT_EQ(std::string("<HTH_Table><th>H6</th><th>H7</th><th>H8</th><th>H9</th><th>H10</th></HTH_Table>"), anImpl.getHeader().ToString());
    //std::cout<<anImpl.getHeader().ToString()<<std::endl;

}

TEST (Header, Set_ConsisntecyCheck_Variadic) {
    unsigned short int test_h=29999;
    unsigned short int test_w=27777;
    HtmlTableHandlerImpl anImpl(test_h, test_w);

    anImpl.setHeader("H1", "H2", "H3", "H4", "H5");
    EXPECT_EQ(anImpl.getHeader().Name() , HTH_DEFAULT_TABLE_NAME);
    EXPECT_EQ(std::string("<HTH_Table><th>H1</th><th>H2</th><th>H3</th><th>H4</th><th>H5</th></HTH_Table>"), anImpl.getHeader().ToString());

    anImpl.setHeader("H6", "H7", "H8", "H9", "H10");
    EXPECT_EQ(anImpl.getHeader().Name() , HTH_DEFAULT_TABLE_NAME);
    EXPECT_EQ(std::string("<HTH_Table><th>H6</th><th>H7</th><th>H8</th><th>H9</th><th>H10</th></HTH_Table>"), anImpl.getHeader().ToString());
    //std::cout<<anImpl.getHeader().ToString()<<std::endl;

}

TEST (Header, Append_ConsisntecyCheck_InitilyzerList) {
    unsigned short int test_h=29999;
    unsigned short int test_w=27777;
    HtmlTableHandlerImpl anImpl(test_h, test_w);
    //Create empty initializer list
    auto aList = {"H1", "H2", "H3", "H4", "H5"};
    anImpl.setHeader(aList);
    EXPECT_EQ(anImpl.getHeader().Name() , HTH_DEFAULT_TABLE_NAME);
    EXPECT_EQ(std::string("<HTH_Table><th>H1</th><th>H2</th><th>H3</th><th>H4</th><th>H5</th></HTH_Table>"), anImpl.getHeader().ToString());

    aList = {"H6", "H7", "H8", "H9", "H10"};
    anImpl.appendHeader(aList);
    EXPECT_EQ(anImpl.getHeader().Name() , HTH_DEFAULT_TABLE_NAME);
    EXPECT_EQ(std::string("<HTH_Table><th>H1</th><th>H2</th><th>H3</th><th>H4</th><th>H5</th><th>H6</th><th>H7</th><th>H8</th><th>H9</th><th>H10</th></HTH_Table>"), anImpl.getHeader().ToString());
    //std::cout<<anImpl.getHeader().ToString()<<std::endl;

}

