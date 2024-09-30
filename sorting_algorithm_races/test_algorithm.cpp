#if TEST_MODE == 1
#include <gtest/gtest.h>
#include "src.h"

// Test for Quick Sort
TEST(SortingAlgorithmTest, QuickSortTest) {
    std::vector<int> vec = { 5, 2, 9, 1, 5, 6 };
    algorithm_ quick("quick sort", "fast boi");
    std::vector<int> result = quick.go(vec);

    std::vector<int> expected = { 1, 2, 5, 5, 6, 9 };
    EXPECT_EQ(result, expected);  // Check if sorted correctly
}

// Test for Stable Sort
TEST(SortingAlgorithmTest, StableSortTest) {
    std::vector<int> vec = { 5, 2, 9, 1, 5, 6 };
    algorithm_ stable("stable sort", "not for horses");
    std::vector<int> result = stable.go(vec);

    std::vector<int> expected = { 1, 2, 5, 5, 6, 9 };
    EXPECT_EQ(result, expected);
}

// Test for Heap Sort
TEST(SortingAlgorithmTest, HeapSortTest) {
    std::vector<int> vec = { 5, 2, 9, 1, 5, 6 };
    algorithm_ heap("heap sort", "heap based");
    std::vector<int> result = heap.go(vec);

    std::vector<int> expected = { 1, 2, 5, 5, 6, 9 };
    EXPECT_EQ(result, expected);
}

// Test for Bubble Sort
TEST(SortingAlgorithmTest, BubbleSortTest) {
    std::vector<int> vec = { 5, 2, 9, 1, 5, 6 };
    algorithm_ bubble("bubble sort", "blop blop");
    std::vector<int> result = bubble.go(vec);

    std::vector<int> expected = { 1, 2, 5, 5, 6, 9 };
    EXPECT_EQ(result, expected);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
#endif
