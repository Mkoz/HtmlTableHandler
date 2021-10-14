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
    auto aList = {"H1", "H2", "H3", "H4", "H5"};
    anImpl.setHeader(aList);
    EXPECT_EQ(anImpl.getHeader().Name() , HTH_DEFAULT_TABLE_NAME);
    EXPECT_EQ(std::string("<HTH_Table><th>H1</th><th>H2</th><th>H3</th><th>H4</th><th>H5</th></HTH_Table>"), anImpl.getHeader().ToString());

    aList = {"H6", "H7", "H8", "H9", "H10"};
    anImpl.setHeader(aList);
    EXPECT_EQ(anImpl.getHeader().Name() , HTH_DEFAULT_TABLE_NAME);
    EXPECT_EQ(std::string("<HTH_Table><th>H6</th><th>H7</th><th>H8</th><th>H9</th><th>H10</th></HTH_Table>"), anImpl.getHeader().ToString());
}

TEST (Header, Set_ConsisntecyCheck_Variadic) {
    unsigned short int test_h=29999;
    unsigned short int test_w=27777;
    HtmlTableHandlerImpl anImpl(test_h, test_w);

    anImpl.setHeader(std::string("H1"), std::string("H2"), std::string("H3"), std::string("H4"), std::string("H5"));
    EXPECT_EQ(anImpl.getHeader().Name() , HTH_DEFAULT_TABLE_NAME);
    EXPECT_EQ(std::string("<HTH_Table><th>H1</th><th>H2</th><th>H3</th><th>H4</th><th>H5</th></HTH_Table>"), anImpl.getHeader().ToString());

    anImpl.setHeader("H6", "H7", "H8", "H9", "H10");
    EXPECT_EQ(anImpl.getHeader().Name() , HTH_DEFAULT_TABLE_NAME);
    EXPECT_EQ(std::string("<HTH_Table><th>H6</th><th>H7</th><th>H8</th><th>H9</th><th>H10</th></HTH_Table>"), anImpl.getHeader().ToString());
}

TEST (Header, Set_ConsisntecyCheck_VariadicDiffTypes) {
    unsigned short int test_h=29999;
    unsigned short int test_w=27777;
    HtmlTableHandlerImpl anImpl(test_h, test_w);

    auto str = std::string("H5");
    auto& str_ref = str;
    const char* char_str = "H3";
    auto& char_str_ref = char_str;
    anImpl.setHeader(std::string("H1"), "H2", char_str_ref, 4, str_ref);
    EXPECT_EQ(anImpl.getHeader().Name() , HTH_DEFAULT_TABLE_NAME);
    EXPECT_EQ(std::string("<HTH_Table><th>H1</th><th>H2</th><th>H3</th><th>4</th><th>H5</th></HTH_Table>"), anImpl.getHeader().ToString());

    auto str_2 = std::string("H10");
    auto& str_ref_2 = str_2;
    const char* char_str_2 = "H9";
    auto& char_str_ref_2 = char_str_2;
    anImpl.setHeader("H6", std::string("H7"), 8, char_str_2, str_ref_2);
    EXPECT_EQ(anImpl.getHeader().Name() , HTH_DEFAULT_TABLE_NAME);
    EXPECT_EQ(std::string("<HTH_Table><th>H6</th><th>H7</th><th>8</th><th>H9</th><th>H10</th></HTH_Table>"), anImpl.getHeader().ToString());
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
}

TEST (Header, Append_ConsisntecyCheck_VariadicDiffTypes) {
    unsigned short int test_h=29999;
    unsigned short int test_w=27777;
    HtmlTableHandlerImpl anImpl(test_h, test_w);

    auto str = std::string("H5");
    auto& str_ref = str;
    const char* char_str = "H3";
    auto& char_str_ref = char_str;
    anImpl.setHeader(std::string("H1"), "H2", char_str_ref, 4, str_ref);
    EXPECT_EQ(anImpl.getHeader().Name() , HTH_DEFAULT_TABLE_NAME);
    EXPECT_EQ(std::string("<HTH_Table><th>H1</th><th>H2</th><th>H3</th><th>4</th><th>H5</th></HTH_Table>"), anImpl.getHeader().ToString());

    auto str_2 = std::string("H10");
    auto& str_ref_2 = str_2;
    const char* char_str_2 = "H9";
    auto& char_str_ref_2 = char_str_2;
    anImpl.appendHeader("H6", std::string("H7"), 8, char_str_2, str_ref_2);
    EXPECT_EQ(anImpl.getHeader().Name() , HTH_DEFAULT_TABLE_NAME);
    EXPECT_EQ(std::string("<HTH_Table><th>H1</th><th>H2</th><th>H3</th><th>4</th><th>H5</th><th>H6</th><th>H7</th><th>8</th><th>H9</th><th>H10</th></HTH_Table>"), anImpl.getHeader().ToString());
}

TEST (Header, Append_AppendEmptyHeader) {
    unsigned short int test_h=29999;
    unsigned short int test_w=27777;
    HtmlTableHandlerImpl anImpl(test_h, test_w);

    auto str = std::string("H5");
    auto& str_ref = str;
    const char* char_str = "H3";
    auto& char_str_ref = char_str;
    anImpl.appendHeader(std::string("H1"), "H2", char_str_ref, 4, str_ref);
    EXPECT_EQ(anImpl.getHeader().Name() , HTH_DEFAULT_TABLE_NAME);
    EXPECT_EQ(std::string("<HTH_Table><th>H1</th><th>H2</th><th>H3</th><th>4</th><th>H5</th></HTH_Table>"), anImpl.getHeader().ToString());
}

TEST (Header, Append_FillTheHeader) {
    unsigned short int test_h=29999;
    unsigned short int test_w=100;
    HtmlTableHandlerImpl anImpl(test_h, test_w);

    auto verifyString = std::string("<HTH_Table>");

    for(unsigned short int i = 0; i < test_w; ++i) {
        auto tmpValue = std::string("HeaderCell_")+std::to_string(i);
        anImpl.appendHeader(tmpValue);
        verifyString += std::string("<th>") + tmpValue + std::string("</th>");
    }
    verifyString += std::string("</HTH_Table>");
    EXPECT_EQ(anImpl.getHeader().Name() , HTH_DEFAULT_TABLE_NAME);
    EXPECT_EQ(verifyString, anImpl.getHeader().ToString());
}
