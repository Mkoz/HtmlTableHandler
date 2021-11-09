#include "gtest/gtest.h"
#include "../Impl/HtmlTableHandlerImpl.h"
#include "../Impl/HTHConst.h"

// TODO 3 -> 100
static int test_value = 3;

void size_test(HtmlTableHandlerImpl& anImpl,const size_t& aH, const size_t& aW) {
    EXPECT_EQ(std::get<0>(anImpl.getSize()), aH);
    EXPECT_EQ(std::get<1>(anImpl.getSize()), aW);
    EXPECT_EQ(anImpl.getHeader().Name() , HTH_ROW_TAG);
}

TEST (DefaultConstructor, ConsisntecyCheck) {
    auto anImpl = HtmlTableHandlerImpl();
    size_test(anImpl, 1, 0);
}

TEST (RemoveRow, Remove_existed) {
    auto anImpl = HtmlTableHandlerImpl();
// TODO 2 -> 20
    int thisTestTmpValue = 2;
    size_test(anImpl, 1, 0);

    for (auto i = 0; i < test_value; ++i) {
        anImpl.addRow("Cell_1", "Cell_2");
    }
    size_test(anImpl, test_value + 1, 2);

    for (auto i = 0; i < thisTestTmpValue; ++i) {
        anImpl.removeRow(0);
        size_test(anImpl, test_value - i, 2);
    }
    size_test(anImpl, test_value + 1 - thisTestTmpValue, 2);
}

TEST (RemoveRow, Remove_non_existed) {
    auto anImpl = HtmlTableHandlerImpl();
    size_test(anImpl, 1, 0);

    for (auto i = 0; i < test_value; ++i) {
        anImpl.addRow("Cell_1", "Cell_2");
    }
    size_test(anImpl, test_value + 1, 2);

    anImpl.removeRow(test_value + 10);
    size_test(anImpl, test_value + 1, 2);
}

TEST (RemoveRow, Remove_all) {
    auto anImpl = HtmlTableHandlerImpl();
    size_test(anImpl, 1, 0);
    for (auto i = 0; i < test_value; ++i) {
        anImpl.addRow("Cell_1", "Cell_2");
        size_test(anImpl, i + 2 , 2);
    }
    size_test(anImpl, test_value + 1, 2);

    for (auto i = 0; i < test_value; ++i) {
        anImpl.removeRow(0);
        if (i == test_value - 1) {
            size_test(anImpl, test_value - i, 0);
        } else {
            size_test(anImpl, test_value - i, 2);
        }
    }
    size_test(anImpl, 1, 0);

}


TEST (RemoveRow, Remove_all_reverse) {
    auto anImpl = HtmlTableHandlerImpl();
    size_test(anImpl, 1, 0);
    for (auto i = 0; i < test_value; ++i) {
        anImpl.addRow("Cell_1", "Cell_2");
        size_test(anImpl, i + 2 , 2);
    }
    size_test(anImpl, test_value + 1, 2);

    for (auto i = test_value; i > 0; --i) {
        anImpl.removeRow(i - 1);
        if (i == 1) {
            size_test(anImpl, i, 0);
        } else {
            size_test(anImpl, i, 2);
        }
    }
    size_test(anImpl, 1, 0);
}
TEST (RemoveRow, Remove_empty) {
    auto anImpl = HtmlTableHandlerImpl();
    size_test(anImpl, 1, 0);
}
/*

TEST (Header, Set_ConsisntecyCheck_InitilyzerList) {
    auto anImpl = HtmlTableHandlerImpl();
    size_test(anImpl, 1, 0);

    auto aList = {"H1", "H2", "H3", "H4", "H5"};
    anImpl.setHeader(aList);
    EXPECT_EQ(std::string("<tr><th>H1</th><th>H2</th><th>H3</th><th>H4</th><th>H5</th></tr>"), anImpl.getHeader().ToString());

    aList = {"H6", "H7", "H8", "H9", "H10"};
    anImpl.setHeader(aList);
    EXPECT_EQ(std::string("<tr><th>H6</th><th>H7</th><th>H8</th><th>H9</th><th>H10</th></tr>"), anImpl.getHeader().ToString());
}

TEST (Header, Set_ConsisntecyCheck_Variadic) {
    auto anImpl = HtmlTableHandlerImpl();
    size_test(anImpl, 1, 0);

    anImpl.setHeader(std::string("H1"), std::string("H2"), std::string("H3"), std::string("H4"), std::string("H5"));
    EXPECT_EQ(std::string("<tr><th>H1</th><th>H2</th><th>H3</th><th>H4</th><th>H5</th></tr>"), anImpl.getHeader().ToString());

    anImpl.setHeader("H6", "H7", "H8", "H9", "H10");
    EXPECT_EQ(std::string("<tr><th>H6</th><th>H7</th><th>H8</th><th>H9</th><th>H10</th></tr>"), anImpl.getHeader().ToString());

}

TEST (Header, Set_ConsisntecyCheck_VariadicDiffTypes) {
    auto anImpl = HtmlTableHandlerImpl();
    size_test(anImpl, 1, 0);

    auto str = std::string("H5");
    auto& str_ref = str;
    const char* char_str = "H3";
    auto& char_str_ref = char_str;
    anImpl.setHeader(std::string("H1"), "H2", char_str_ref, 4, str_ref);
    EXPECT_EQ(std::string("<tr><th>H1</th><th>H2</th><th>H3</th><th>4</th><th>H5</th></tr>"), anImpl.getHeader().ToString());

    auto str_2 = std::string("H10");
    auto& str_ref_2 = str_2;
    const char* char_str_2 = "H9";
    auto& char_str_ref_2 = char_str_2;
    anImpl.setHeader("H6", std::string("H7"), 8, char_str_2, str_ref_2);
    EXPECT_EQ(std::string("<tr><th>H6</th><th>H7</th><th>8</th><th>H9</th><th>H10</th></tr>"), anImpl.getHeader().ToString());
}

TEST (Header, Append_ConsisntecyCheck_InitilyzerList) {
    auto anImpl = HtmlTableHandlerImpl();
    size_test(anImpl, 1, 0);

    auto aList = {"H1", "H2", "H3", "H4", "H5"};
    anImpl.setHeader(aList);
    EXPECT_EQ(std::string("<tr><th>H1</th><th>H2</th><th>H3</th><th>H4</th><th>H5</th></tr>"), anImpl.getHeader().ToString());

    aList = {"H6", "H7", "H8", "H9", "H10"};
    anImpl.appendHeader(aList);
    EXPECT_EQ(std::string("<tr><th>H1</th><th>H2</th><th>H3</th><th>H4</th><th>H5</th><th>H6</th><th>H7</th><th>H8</th><th>H9</th><th>H10</th></tr>"), anImpl.getHeader().ToString());
}

TEST (Header, Append_ConsisntecyCheck_VariadicDiffTypes) {
    auto anImpl = HtmlTableHandlerImpl();
    size_test(anImpl, 1, 0);

    auto str = std::string("H5");
    auto& str_ref = str;
    const char* char_str = "H3";
    auto& char_str_ref = char_str;
    anImpl.appendHeader(std::string("H1"), "H2", char_str_ref, 4, str_ref);
    EXPECT_EQ(std::string("<tr><th>H1</th><th>H2</th><th>H3</th><th>4</th><th>H5</th></tr>"), anImpl.getHeader().ToString());

    auto str_2 = std::string("H10");
    auto& str_ref_2 = str_2;
    const char* char_str_2 = "H9";
    auto& char_str_ref_2 = char_str_2;
    anImpl.appendHeader("H6", std::string("H7"), 8, char_str_2, str_ref_2);
    EXPECT_EQ(std::string("<tr><th>H1</th><th>H2</th><th>H3</th><th>4</th><th>H5</th><th>H6</th><th>H7</th><th>8</th><th>H9</th><th>H10</th></tr>"), anImpl.getHeader().ToString());
}

TEST (Header, Append_AppendEmptyHeader) {
    auto anImpl = HtmlTableHandlerImpl();
    size_test(anImpl, 1, 0);

    auto str = std::string("H5");
    auto& str_ref = str;
    const char* char_str = "H3";
    auto& char_str_ref = char_str;
    anImpl.appendHeader(std::string("H1"), "H2", char_str_ref, 4, str_ref);
    EXPECT_EQ(std::string("<tr><th>H1</th><th>H2</th><th>H3</th><th>4</th><th>H5</th></tr>"), anImpl.getHeader().ToString());
}

TEST (Header, Append_FillTheHeader) {
    auto anImpl = HtmlTableHandlerImpl();
    size_test(anImpl, 1, 0);

    const size_t test_w = 100;
    auto verifyString = std::string("<tr>");

    for(unsigned short int i = 0; i < test_w; ++i) {
        auto tmpValue = std::string("HeaderCell_")+std::to_string(i);
        anImpl.appendHeader(tmpValue);
        verifyString += std::string("<th>") + tmpValue + std::string("</th>");
    }
    verifyString += std::string("</tr>");
    EXPECT_EQ(verifyString, anImpl.getHeader().ToString());
    size_test(anImpl, 1, test_w);

}

TEST (Row, Set_ConsictencyCheck) {
    auto anImpl = HtmlTableHandlerImpl();
    size_test(anImpl, 1, 0);

    auto verifyString = std::string("<tr>");
    auto tmpValue = std::string("<tr>");
    const size_t test_w = 100;

    for (unsigned short int i = 0; i < test_w; ++i) {

        auto str = std::string("H5");
        auto& str_ref = str;
        const char* char_str = "H3";
        auto& char_str_ref = char_str;
        anImpl.setRow(i, std::string("H1"), "H2", char_str_ref, 4, str_ref);
        EXPECT_EQ(std::string("<tr><td>H1</td><td>H2</td><td>H3</td><td>4</td><td>H5</td></tr>"), anImpl.getBody()[i]->ToString());
    }
    size_test(anImpl, test_w + 1, 5);
}

TEST (Row, Set_ListConsictencyCheck) {
    auto anImpl = HtmlTableHandlerImpl();
    size_test(anImpl, 1, 0);

    auto verifyString = std::string("<tr>");
    auto tmpValue = std::string("<tr>");
    const size_t test_w = 100;

    for (unsigned short int i = 0; i < test_w; ++i) {

        auto aList = {"H1", "H2", "H3", "H4", "H5"};
//PRINT << i << std::endl;
        anImpl.setRow(i, aList);
    }
    PRINT << std::get<0>(anImpl.getSize()) << std::endl;
    PRINT << std::get<1>(anImpl.getSize()) << std::endl;
    PRINT << "Body:: " << anImpl.getBody().size()  << std::endl;

    size_test(anImpl, test_w + 1, 5);
    for (unsigned short int i = 0; i < test_w; ++i) {
        EXPECT_EQ(std::string("<tr><th>H1</th><th>H2</th><th>H3</th><th>H4</th><th>H5</th></tr>"), anImpl.getBody()[i]->ToString());
    }
}
 */