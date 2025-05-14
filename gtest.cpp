#include <gtest/gtest.h>
#include "Histogram.h"
#include <vector>
#include <stdexcept>
#include <map>

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

TEST(GystogrammTest, BasicBins) {
    std::vector<double> data = {1, 2, 3};
    Histogram g(data, 1.0, 4.0, 3);
    std::vector<size_t> expected = {1,1,1};
    for (auto it = g.begin(); it != g.end(); ++it) {
        EXPECT_EQ(g.at(it), expected[g.id(it)]);
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

TEST(GystogrammOperators, NegativeCountThrows) {
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
    EXPECT_FALSE(g1 != g3);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
