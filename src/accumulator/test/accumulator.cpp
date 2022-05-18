#include <gtest/gtest.h>

#include <accumulator/accumulator.hpp>

TEST(accumulator, load_once) {
    constexpr int SIZE = 1;
    dys::accumulator<std::uint32_t> acc(SIZE, 0, std::vector<std::uint32_t>(SIZE));

    acc.load(42);
    
    ASSERT_EQ(acc.count(), 1);
    ASSERT_EQ(acc.level(), 42);

    SUCCEED();
}

TEST(accumulator, count) {
    constexpr int SIZE = 3;
    dys::accumulator<std::uint32_t> acc(SIZE, 0, std::vector<std::uint32_t>(SIZE));

    ASSERT_EQ(acc.count(), 0);
    for (int i = 1; i <= SIZE; i++) {
        acc.load(42);
        ASSERT_EQ(acc.count(), i);
    }
    
    ASSERT_EQ(acc.count(), SIZE);
    ASSERT_EQ(acc.level(), 42 * SIZE);

    SUCCEED();
}

TEST(accumulator, init_charge) {
    constexpr int SIZE = 1;
    dys::accumulator<std::uint32_t> acc(SIZE, 42, std::vector<std::uint32_t>(SIZE));

    acc.load(42);

    ASSERT_EQ(acc.count(), 1);
    ASSERT_EQ(acc.level(), 84);

    SUCCEED();
}

TEST(accumulator, rw_storage) {
    dys::accumulator<std::uint32_t> acc(5, 0, std::vector<std::uint32_t>(5));

    acc.load(100);
    acc.load(1);
    acc.load(1);
    acc.load(1);
    acc.load(1);

    acc.load(1);
    ASSERT_EQ(acc.count(), 5);
    ASSERT_EQ(acc.level(), 5);

    SUCCEED();
}

TEST(accumulator, discharge) {
    constexpr int SIZE = 5;
    dys::accumulator<std::uint32_t> acc(SIZE, 0, std::vector<std::uint32_t>(SIZE));

    auto discharge = acc.load(2);
    ASSERT_EQ(discharge, std::nullopt);
    
    for (int i = 1; i < SIZE; i++) {
        discharge = acc.load(1);
        ASSERT_EQ(discharge, std::nullopt);
    }

    discharge = acc.load(1);
    ASSERT_TRUE(discharge.has_value());
    auto discharge_v = discharge.value();
    ASSERT_EQ(discharge_v, 2);

    SUCCEED();
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
