#include <gtest/gtest.h>
#include "Histogram.h"
#include <vector>
#include <stdexcept>
#include <fstream>
#include "Parser.h"

// TEST Parser

TEST(Parser, Valid) {
    std::istringstream input("1 2 3 4 5 6 7 8 9 ");
    std::vector<double> expected = {1,2,3,4,5,6,7,8,9};
    EXPECT_EQ(Parser::get_data(input), expected);
}

TEST(Parser, EmptyInput) {
    std::istringstream input("");
    EXPECT_THROW(Parser::get_data(input), std::runtime_error);
}

TEST(Parser, OneMbFile) {
    std::ifstream in("OneMbFile.txt");
    if (!in.is_open()) {
        std::cout << "OneMbFile cant be tested - no file OneMbFile.txt" << std::endl;
        return;
    }
    in.close();
    std::vector<double> data = Parser::get_data(in);
    for (int i = 1; i <= data.size(); i++) {
        EXPECT_EQ(data[i], i);
    }
}

// TEST HISTOGRAM

TEST(GystogrammTest, BasicBins) {
    std::vector<double> data = {1, 2, 3};
    Histogram g(data, 1.0, 4.0, 3);
    std::vector<size_t> expected = {1,1,1};
    for (auto it = g.begin(); it != g.end(); ++it) {
        EXPECT_EQ(g.at(it), expected[g.id(it)]);
    }
}

TEST(GystogrammTest, OneMbFile) {
    std::ifstream in("OneMbFile.txt");
    if (!in.is_open()) {
        std::cout << "OneMbFile cant be tested - no file OneMbFile.txt" << std::endl;
        return;
    }
    Histogram g1(1, 1000, 1000000);
    Histogram g2(1, 1000, 500000);
    while (Parser::finish != true) {
        auto data = Parser::get_data(in);
        g1.add(data);
        g2.add(data);
    }
    in.close();
    std::vector<size_t> expected = {};
    expected.resize(1000000,1);
    for (auto it = g1.begin(); it != g1.end(); ++it) {
        EXPECT_EQ(g1.at(it), expected[g1.id(it)]);
    }
    expected.resize(500000,2);
    for (auto it = g2.begin(); it != g2.end(); ++it) {
        EXPECT_EQ(g2.at(it), expected[g2.id(it)]);
    }

}

TEST(GystogrammTest, VariateMaxMinBin_count) {
    // max-min < bin_count
    std::vector<double> data1 = {-1,-1,-1,-1, 1, 0.1, 0.2, 2, 3, 4, 5, 6, 7, 8, 9};
    Histogram g1(data1, 1.0, 4.0, 9);
    std::vector<size_t> expected1 = {7,0,0,1,0,0,1,0,6};
    for (auto it = g1.begin(); it != g1.end(); ++it) {
        EXPECT_EQ(g1.at(it), expected1[g1.id(it)]);
    }
    // max-min > bin_count
    std::vector<double> data2 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    Histogram g2(data2, 1.0, 10, 3);
    std::vector<size_t> expected2 = {3,3,3};
    for (auto it = g2.begin(); it != g2.end(); ++it) {
        std::cout << g2.at(it) << std::endl;
        EXPECT_EQ(g2.at(it), expected2[g2.id(it)]);
    }
    // max-min = bin_count
    std::vector<double> data3 = {1, 2, 3,3,3,3,10};
    Histogram g3(data3, 1.0, 4.0, 3);
    std::vector<size_t> expected3 = {1,1,5};
    for (auto it = g3.begin(); it != g3.end(); ++it) {
        EXPECT_EQ(g3.at(it), expected3[g3.id(it)]);
    }

}

TEST(GystogrammTest, UnderOverflow) {
    std::vector<double> data = {0, 5};
    Histogram g(data, 1.0, 4.0, 3);
    std::vector<size_t> expected = {1,0,1};
    for (auto it = g.begin(); it != g.end(); ++it) {
        EXPECT_EQ(g.at(it), expected[g.id(it)]);
    }
}

TEST(GystogrammOperators, Addition) {
    Histogram g1({1,2}, 1.0, 4.0, 3);
    Histogram g2({2,3}, 1.0, 4.0, 3);
    Histogram sum = g1 + g2;
    std::vector<size_t> expected = {1,2,1};
    for (auto it = sum.begin(); it != sum.end(); ++it) {
        EXPECT_EQ(sum.at(it), expected[sum.id(it)]);
    }
}

TEST(GystogrammOperators, Subtraction) {
    Histogram g1({1,2,2}, 1.0, 4.0, 3);
    Histogram g2({2}, 1.0, 4.0, 3);
    Histogram diff = g1 - g2;
    std::vector<size_t> expected = {1,1,0};
    for (auto it = diff.begin(); it != diff.end(); ++it) {
        EXPECT_EQ(diff.at(it), expected[diff.id(it)]);
    }
}

TEST(GystogrammOperators, MismatchParamsThrows) {
    Histogram g1({1}, 1.0, 4.0, 3);
    Histogram g2({1}, 0.0, 4.0, 3);
    EXPECT_THROW(g1 + g2, std::runtime_error);
    EXPECT_THROW(g1 - g2, std::runtime_error);
}

TEST(GystogrammOperators, NegativeCount) {
    Histogram g1({1}, 1.0, 4.0, 3);
    Histogram g2({1,1}, 1.0, 4.0, 3);
    auto diff = g1 - g2;
    std::vector<size_t> expected = {0,0,0};
    for (auto it = diff.begin(); it != diff.end(); ++it) {
        EXPECT_EQ(diff.at(it), expected[diff.id(it)]);
    }
}

TEST(GystogrammOperators, Comparings) {
    Histogram g1({1,2}, 1.0, 4.0, 3);
    Histogram g2({1,2}, 1.0, 4.0, 3);
    Histogram g3({3,4}, 0.0, 4.0, 3);
    Histogram g4({5,5}, 1.0, 4.0, 3);

    EXPECT_TRUE(g1 == g2);
    EXPECT_FALSE(g1 == g3);
    EXPECT_TRUE(g1 != g4);
    EXPECT_TRUE(g1 != g3);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
