#include "astar.hpp"
#include "gmock/gmock.h"
#include <gtest/gtest.h>

using namespace testing;

TEST(astar, Simple) {
    W = 5;
    H = 3;
    matrix<double> m = {
        {INF, INF, INF}, {2.5, 1.0, 1.0}, {2.5, 6.0, 1.5}, {2.5, 1.0, 1.0}, {INF, INF, INF},
    };

    coords init = {1, 1};

    assert(init.fi < W && init.se < H);

    coords goal = {3, 1};

    assert(goal.fi < W && goal.se < H);

    constexpr double expected_cost = 4.5;
    const vector<coords> expected_path = {{1, 1}, {1, 2}, {2, 2}, {3, 2}, {3, 1}};

    Path path = astar(m, init, goal);

    EXPECT_EQ(expected_cost, path.second);
}

TEST(astar, Death) {
    W = 5;
    H = 3;
    matrix<double> m = {
        {INF, INF, INF}, {INF, 1.0, INF}, {INF, INF, INF}, {2.5, 1.0, 1.0}, {INF, INF, INF},
    };
    coords init = {1, 1};
    coords goal = {3, 1};
    EXPECT_THAT([&]() { astar(m, init, goal); },
                ThrowsMessage<runtime_error>(NO_PATH_FOUND_MESSAGE));
}
