#include "ids.hpp"
#include "gmock/gmock.h"
#include <gtest/gtest.h>

using namespace testing;

TEST(dls, InitEqualsGoal) {
    W = 3;
    H = 3;
    coords init;
    coords goal;
    init = goal = {1, 1};
    matrix<double> m = {
        {INF, INF, INF},
        {INF, 1.0, INF},
        {INF, INF, INF},
    };

    auto path = dls(m, init, goal, 0);

    constexpr double expected_cost = 0.0;
    const vector<coords> expected_path = {};

    EXPECT_TRUE(path.has_value());
    EXPECT_EQ(path->second, expected_cost);
    EXPECT_EQ(path->first, expected_path);
}

TEST(dls, cantFindDeepGoal) {
    W = 3;
    H = 3;
    coords init = {1, 1};
    coords goal = {1, 2};
    matrix<double> m = {
        {INF, INF, INF},
        {INF, 1.0, 1.0},
        {INF, INF, INF},
    };

    auto path = dls(m, init, goal, 0);

    EXPECT_FALSE(path.has_value());
}

TEST(dls, canFindDepthOne) {
    W = 3;
    H = 3;
    coords init = {1, 1};
    coords goal = {1, 2};
    matrix<double> m = {
        {INF, INF, INF},
        {INF, 1.0, 1.0},
        {INF, INF, INF},
    };

    auto path = dls(m, init, goal, 1);

    constexpr double expected_cost = 1.0;
    const vector<coords> expected_path = {{1, 2}};

    EXPECT_TRUE(path.has_value());
    EXPECT_EQ(path->second, expected_cost);
    EXPECT_EQ(path->first, expected_path);
}

TEST(dls, canFindDepthTwo) {
    W = 3;
    H = 3;
    coords init = {0, 0};
    coords goal = {2, 0};
    matrix<double> m = {
        {1.0, 1.0, 1.0},
        {1.5, 1.0, 1.0},
        {1.0, 1.0, 1.0},
    };

    auto path = dls(m, init, goal, 2);

    constexpr double expected_cost = 2.5;
    const vector<coords> expected_path = {{1, 0}, {2, 0}};

    EXPECT_TRUE(path.has_value());
    EXPECT_EQ(path->second, expected_cost);
    EXPECT_EQ(path->first, expected_path);
}

TEST(dls, canDodgeObstacle) {
    W = 3;
    H = 3;
    coords init = {1, 0};
    coords goal = {1, 2};
    matrix<double> m = {
        {1.5, 1.0, 1.5},
        {1.0, INF, 1.0},
        {1.0, 1.5, 1.0},
    };

    auto path = dls(m, init, goal, 4);

    constexpr double expected_cost = 4.5;
    const vector<coords> expected_path = {{2, 0}, {2, 1}, {2, 2}, {1, 2}};

    EXPECT_TRUE(path.has_value());
    EXPECT_EQ(path->second, expected_cost);
    EXPECT_EQ(path->first, expected_path);
}

TEST(dls, pathIsReconstructedCorrectly) {
    W = 3;
    H = 4;
    coords init = {0, 0};
    coords goal = {1, 3};

    matrix<double> m = {
        {1., 1., 1., INF},
        {1., 1., 1., 1.},
        {1., 1., 1., INF},
    };

    auto path = dls(m, init, goal, 4);

    constexpr int expected_depth = 4;
    constexpr double expected_cost = 4.;
    const vector<coords> expected_path = {{1, 0}, {1, 1}, {1, 2}, {1, 3}};

    EXPECT_EQ(path->second, expected_cost);
    EXPECT_EQ(path->first, expected_path);
    EXPECT_EQ(path->first.size(), expected_depth);

    // The actual cost is calculated independently from the path
    double path_cost =
        accumulate(path->first.begin(), path->first.end(), 0.0,
                   [&m](double sum, const auto &step) { return sum + m.at(step.fi).at(step.se); });

    EXPECT_EQ(path_cost, path->second);
}

TEST(dls, orderOfDirectionsMayCausePathToNotBeFound) {
    W = 3;
    H = 4;
    coords init = {0, 0};
    coords goal = {1, 3};
    matrix<double> m = {
        {1., 1., 1., INF},
        {1., 1., 1., 1.},
        {1., 1., 1., INF},
    };

    auto path = dls(m, init, goal, 5);

    // In spite of not finding the path here, if running the ids, a path is found with depth 4
    EXPECT_FALSE(path.has_value());
}

TEST(dls, pathIsEventuallyFoundInSpiteOfOrderOfDirections) {
    W = 3;
    H = 4;
    coords init = {0, 0};
    coords goal = {1, 3};
    matrix<double> m = {
        {1., 1., 1., INF},
        {1., 1., 1., 1.},
        {1., 1., 1., INF},
    };

    auto path = dls(m, init, goal, 6);

    constexpr double expected_cost = 6;
    const vector<coords> expected_path = {{1, 0}, {2, 0}, {2, 1}, {2, 2}, {1, 2}, {1, 3}};

    EXPECT_TRUE(path.has_value());
    EXPECT_EQ(path->second, expected_cost);
    EXPECT_EQ(path->first, expected_path);
}

TEST(ids, pathIsFoundIfItExists) {
    W = 3;
    H = 4;
    coords init = {0, 0};
    coords goal = {1, 3};
    matrix<double> m = {
        {1., 1., 1., INF},
        {1., 1., 1., 1.},
        {1., 1., 1., INF},
    };

    constexpr double expected_cost = 4.;
    const vector<coords> expected_path = {{1, 0}, {1, 1}, {1, 2}, {1, 3}};

    Path path = ids(m, init, goal);

    EXPECT_EQ(path.second, expected_cost);
    EXPECT_EQ(path.first, expected_path);
}

TEST(ids, Simple) {
    W = 5;
    H = 3;
    matrix<double> m = {
        {INF, INF, INF}, {2.5, 1.0, 1.0}, {2.5, 6.0, 1.5}, {2.5, 1.0, 1.0}, {INF, INF, INF},
    };

    coords init = {1, 1};
    coords goal = {3, 1};

    constexpr double expected_cost = 7.0;
    const vector<coords> expected_path = {{1, 1}, {2, 1}, {3, 1}};

    Path path = ids(m, init, goal);

    EXPECT_EQ(expected_cost, path.second);
}

TEST(ids, Death) {
    W = 5;
    H = 3;

    matrix<double> m = {
        {INF, INF, INF}, {INF, 1.0, INF}, {INF, INF, INF}, {2.5, 1.0, 1.0}, {INF, INF, INF},
    };
    coords init = {1, 1};
    coords goal = {3, 1};

    EXPECT_THAT([&]() { ids(m, init, goal); }, ThrowsMessage<runtime_error>(NO_PATH_FOUND_MESSAGE));
}
