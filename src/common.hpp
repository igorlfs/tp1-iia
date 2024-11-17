#include <bits/stdc++.h>

#define fi first
#define se second

using namespace std;

using matrix = vector<vector<double>>;
using coords = pair<int, int>;
using Path = pair<vector<coords>, double>;

constexpr int INF = 0x3f3f3f3f;

const vector<coords> DIRECTIONS = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

extern int W, H;

inline bool is_within_bounds(int x, int y) {
    return x >= 0 && x < W && y >= 0 && y < H;
}
