#include <gtest/gtest.h>
#include "Gystogramm.h"
#include <vector>
#include <stdexcept>
#include <map>

TEST(GystogrammTest, BasicBins) {
    std::vector<double> data = {1, 2, 3};
    Gystogramm g(data, 1.0, 4.0, 3);
    std::map<std::size_t, std::size_t> expected = {{0,1},{1,1},{2,1}};
    for (auto it = g.begin(); it != g.end(); ++it) {
        EXPECT_EQ(it->second, expected.at(it->first));
    }
}

TEST(GystogrammTest, UnderOverflow) {
    std::vector<double> data = {0, 5};
    Gystogramm g(data, 1.0, 4.0, 3);
    std::map<std::size_t, std::size_t> expected = {{0,1},{1,0},{2,1}};
    for (auto it = g.begin(); it != g.end(); ++it) {
        EXPECT_EQ(it->second, expected.at(it->first));
    }
}

TEST(GystogrammOperators, Addition) {
    Gystogramm g1({1,2}, 1.0, 4.0, 3);
    Gystogramm g2({2,3}, 1.0, 4.0, 3);
    Gystogramm sum = g1 + g2;
    std::map<std::size_t, std::size_t> expected = {{0,1},{1,2},{2,1}};
    for (auto it = sum.begin(); it != sum.end(); ++it) {
        EXPECT_EQ(it->second, expected.at(it->first));
    }
}

TEST(GystogrammOperators, Subtraction) {
    Gystogramm g1({1,2,2}, 1.0, 4.0, 3);
    Gystogramm g2({2}, 1.0, 4.0, 3);
    Gystogramm diff = g1 - g2;
    std::map<std::size_t, std::size_t> expected = {{0,1},{1,1},{2,0}};
    for (auto it = diff.begin(); it != diff.end(); ++it) {
        EXPECT_EQ(it->second, expected.at(it->first));
    }
}

TEST(GystogrammOperators, MismatchParamsThrows) {
    Gystogramm g1({1}, 1.0, 4.0, 3);
    Gystogramm g2({1}, 0.0, 4.0, 3);
    EXPECT_THROW(g1 + g2, std::runtime_error);
    EXPECT_THROW(g1 - g2, std::runtime_error);
}

TEST(GystogrammOperators, NegativeCountThrows) {
    Gystogramm g1({1}, 1.0, 4.0, 3);
    Gystogramm g2({1,1}, 1.0, 4.0, 3);
    EXPECT_THROW(g1 - g2, std::runtime_error);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
