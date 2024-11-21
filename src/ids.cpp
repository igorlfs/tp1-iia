#include "ids.hpp"

constexpr coords UNVISITED = {-1, -1};

Path ids(matrix<double> &M, coords &init, coords &goal) {
    int upper_bound_search_depth = W * H;

    for (int depth = 0; depth <= upper_bound_search_depth; depth++) {
        if (auto path = dls(M, init, goal, depth)) {
            return *path;
        }
    }

    throw runtime_error(NO_PATH_FOUND_MESSAGE);
}

optional<Path> dls(matrix<double> &M, coords &init, coords &goal, int max_depth) {
    stack<tuple<int, double, coords>> stk;
    matrix<coords> parent(W, vector<coords>(H, UNVISITED));

    stk.emplace(0, 0.0, init);

    while (!stk.empty()) {
        auto [current_depth, current_cost, current_coords] = stk.top();
        stk.pop();

        // If the depth has exceeded, we should backtrack
        if (current_depth > max_depth) {
            continue;
        }

        // Otherwise we might have hit the goal
        if (current_coords == goal) {
            vector<coords> path = rebuild_path(goal, init, parent);

            return make_pair(path, current_cost);
        }

        // If the current node isn't the goal but the depth threshold was hit, we should backtrack
        if (current_depth == max_depth) {
            continue;
        }

        // The order of the previous checks is important
        // We can't check if we hit the goal if the depth has exceeded
        // There might a cleverer way to write these checks

        int x = current_coords.fi;
        int y = current_coords.se;

        for (const auto &[dx, dy] : DIRECTIONS) {
            int new_x = x + dx;
            int new_y = y + dy;

            if (is_within_bounds(new_x, new_y) && M.at(new_x).at(new_y) != INF &&
                parent.at(new_x).at(new_y) == UNVISITED) {
                parent.at(new_x).at(new_y) = {x, y};

                double new_cost = current_cost + M.at(new_x).at(new_y);

                stk.push({current_depth + 1, new_cost, {new_x, new_y}});
            }
        }
    }

    return {};
}
