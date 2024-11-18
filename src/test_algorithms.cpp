#include "bfs.hpp"
#include "ids.hpp"
#include "ucs.hpp"
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

TEST(bfs, Death) {
    W = 5;
    H = 3;
    matrix m = {
        {INF, INF, INF}, {INF, 1.0, INF}, {INF, INF, INF}, {2.5, 1.0, 1.0}, {INF, INF, INF}};
    coords init = {1, 1};
    coords goal = {3, 1};
    ASSERT_DEATH(bfs(m, init, goal), "A path should always exist");
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

    Path path = ids(m, init, goal);

    EXPECT_EQ(expected_cost, path.second);
}

TEST(ids, Death) {
    W = 5;
    H = 3;
    matrix m = {
        {INF, INF, INF}, {INF, 1.0, INF}, {INF, INF, INF}, {2.5, 1.0, 1.0}, {INF, INF, INF}};
    coords init = {1, 1};
    coords goal = {3, 1};
    ASSERT_DEATH(ids(m, init, goal), "A path should always exist");
}

TEST(ucs, Simple) {
    W = 5;
    H = 3;
    matrix m = {
        {INF, INF, INF}, {2.5, 1.0, 1.0}, {2.5, 6.0, 1.5}, {2.5, 1.0, 1.0}, {INF, INF, INF}};

    coords init = {1, 1};

    assert(init.fi < W && init.se < H);

    coords goal = {3, 1};

    assert(goal.fi < W && goal.se < H);

    constexpr double expected_cost = 4.5;
    const vector<coords> expected_path = {{1, 1}, {1, 2}, {2, 2}, {3, 2}, {3, 1}};

    Path path = ucs(m, init, goal);

    EXPECT_EQ(expected_cost, path.second);
}

TEST(ucs, Death) {
    W = 5;
    H = 3;
    matrix m = {
        {INF, INF, INF}, {INF, 1.0, INF}, {INF, INF, INF}, {2.5, 1.0, 1.0}, {INF, INF, INF}};
    coords init = {1, 1};
    coords goal = {3, 1};
    ASSERT_DEATH(ucs(m, init, goal), "A path should always exist");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
