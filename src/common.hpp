#pragma once

#include <bits/stdc++.h>

#define fi first
#define se second

using namespace std;

using matrix = vector<vector<double>>;
using coords = pair<int, int>;
using Path = pair<vector<coords>, double>;

using State = pair<double, pair<coords, vector<coords>>>;

constexpr int INF = 0x3f3f3f3f;

const vector<coords> DIRECTIONS = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

const string NO_PATH_FOUND_MESSAGE = "A path should always exist";

extern int W, H;

inline bool is_within_bounds(int x, int y) {
    return x >= 0 && x < W && y >= 0 && y < H;
}

inline vector<coords> rebuild_path(coords goal, coords init, vector<vector<coords>> &parent) {
    vector<coords> path;

    for (coords step = goal; step != init;) {
        path.push_back(step);
        step = parent.at(step.fi).at(step.se);
    }
    path.push_back(init);

    reverse(path.begin(), path.end());

    return path;
}
