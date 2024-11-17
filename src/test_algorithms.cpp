#include "bfs.hpp"
#include <gtest/gtest.h>

int W, H;

TEST(bfs, Simple) {
    W = 5;
    H = 3;
    matrix m = {
        {INF, INF, INF}, {2.5, 1.0, 1.0}, {2.5, 6.0, 1.5}, {2.5, 1.0, 1.0}, {INF, INF, INF}};

    coords init = {1, 1};

    assert(init.fi < W && init.se < H);

    coords goal = {3, 1};

    assert(goal.fi < W && goal.se < H);

    constexpr double expected_cost = 7.0;
    const vector<coords> expected_path = {{1, 1}, {2, 1}, {3, 1}};

    Path path = bfs(m, init, goal);

    EXPECT_EQ(expected_cost, path.second);
}

TEST(ids, Simple) {
    W = 5;
    H = 3;
    matrix m = {
        {INF, INF, INF}, {2.5, 1.0, 1.0}, {2.5, 6.0, 1.5}, {2.5, 1.0, 1.0}, {INF, INF, INF}};

    coords init = {1, 1};

    assert(init.fi < W && init.se < H);

    coords goal = {3, 1};

    assert(goal.fi < W && goal.se < H);

    constexpr double expected_cost = 7.0;
    const vector<coords> expected_path = {{1, 1}, {2, 1}, {3, 1}};

    Path path = bfs(m, init, goal);

    EXPECT_EQ(expected_cost, path.second);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
