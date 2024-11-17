#include "ids.hpp"

bool dls(matrix &M, coords current, coords &goal, int depth, vector<coords> &path, double &cost,
         vector<vector<bool>> &visited);

Path ids(matrix &M, coords &init, coords &goal) {
    int depth = 0;
    int upper_bound_search_depth = W * H;

    while (depth <= upper_bound_search_depth) {
        vector<coords> path;
        double cost = 0.0;
        vector<vector<bool>> visited(W, vector<bool>(W));

        if (dls(M, init, goal, depth, path, cost, visited)) {
            return {path, cost};
        }

        depth++;
    }

    cerr << "A path should always exist\n";
    exit(1);
}

bool dls(matrix &M, coords current, coords &goal, int depth, vector<coords> &path, double &cost,
         vector<vector<bool>> &visited) {
    if (current == goal) {
        path.push_back(current);
        return true;
    }

    if (depth <= 0) {
        return false;
    }

    int x = current.fi;
    int y = current.se;

    visited.at(x).at(y) = true;
    path.push_back(current);

    for (const auto &[dx, dy] : DIRECTIONS) {
        int new_x = x + dx;
        int new_y = y + dy;

        if (is_within_bounds(new_x, new_y) && !visited.at(new_x).at(new_y) &&
            M.at(new_x).at(new_y) != INF) {
            double next_cost = cost + M.at(new_x).at(new_y);
            if (dls(M, {new_x, new_y}, goal, depth - 1, path, next_cost, visited)) {
                cost = next_cost;
                return true;
            }
        }
    }

    path.pop_back();
    visited.at(x).at(y) = false;
    return false;
}
