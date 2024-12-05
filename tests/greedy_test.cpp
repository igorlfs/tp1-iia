#include "greedy.hpp"
#include "gmock/gmock.h"
#include <gtest/gtest.h>

using namespace testing;

TEST(greedy, Simple) {
    W = 5;
    H = 3;
    matrix<double> m = {
        {INF, INF, INF}, {2.5, 1.0, 1.0}, {2.5, 6.0, 1.5}, {2.5, 1.0, 1.0}, {INF, INF, INF},
    };

    coords init = {1, 1};
    coords goal = {3, 1};

    const vector<coords> expected_path = {{2, 1}, {3, 1}};

    vector<coords> path = greedy(m, init, goal);

    EXPECT_EQ(path, expected_path);
}

TEST(greedy, Death) {
    W = 5;
    H = 3;

    matrix<double> m = {
        {INF, INF, INF}, {INF, 1.0, INF}, {INF, INF, INF}, {2.5, 1.0, 1.0}, {INF, INF, INF},
    };
    coords init = {1, 1};
    coords goal = {3, 1};

    EXPECT_THAT([&]() { greedy(m, init, goal); },
                ThrowsMessage<runtime_error>(NO_PATH_FOUND_MESSAGE));
}
