#include "ids.hpp"

vector<coords> ids(matrix<double> &M, coords &init, coords &goal) {
    int upper_bound_search_depth = W * H;

    for (int depth = 0; depth <= upper_bound_search_depth; depth++) {
        if (auto path = dls(M, init, goal, depth)) {
            return *path;
        }
    }

    throw runtime_error(NO_PATH_FOUND_MESSAGE);
}

optional<vector<coords>> dls(matrix<double> &M, coords &init, coords &goal, int max_depth) {
    stack<pair<int, coords>> stk;
    matrix<coords> parent(W, vector<coords>(H, UNVISITED));

    stk.emplace(0, init);

    while (!stk.empty()) {
        auto [current_depth, node] = stk.top();
        stk.pop();

        // We might have hit the goal
        if (node == goal) {
            return rebuild_path(goal, init, parent);
        }

        // If the current node isn't the goal but the depth threshold was hit, we should backtrack
        if (current_depth == max_depth) {
            continue;
        }

        int x = node.fi;
        int y = node.se;

        for (const auto &[dx, dy] : DIRECTIONS) {
            int new_x = x + dx;
            int new_y = y + dy;

            if (is_within_bounds(new_x, new_y) && M.at(new_x).at(new_y) != INF &&
                parent.at(new_x).at(new_y) == UNVISITED) {
                parent.at(new_x).at(new_y) = {x, y};

                stk.push({current_depth + 1, {new_x, new_y}});
            }
        }
    }

    return {};
}
