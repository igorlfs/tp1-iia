#include "bfs.hpp"

Path bfs(matrix<double> &M, coords &init, coords &goal) {
    matrix<bool> visited(W, vector<bool>(H));
    queue<State> q;
    matrix<coords> parent(W, vector<coords>(H, {-1, -1}));

    q.push({0.0, {init}});

    visited.at(init.fi).at(init.se) = true;

    while (!q.empty()) {
        auto [current_cost, current_coords] = q.front();
        q.pop();

        if (current_coords == goal) {
            vector<coords> path = rebuild_path(goal, init, parent);

            return make_pair(path, current_cost);
        }

        int x = current_coords.fi;
        int y = current_coords.se;

        for (const auto &[dx, dy] : DIRECTIONS) {
            int new_x = x + dx;
            int new_y = y + dy;

            if (is_within_bounds(new_x, new_y) && !visited.at(new_x).at(new_y) &&
                M.at(new_x).at(new_y) != INF) {
                visited.at(new_x).at(new_y) = true;

                parent.at(new_x).at(new_y) = {x, y};

                double new_cost = current_cost + M.at(new_x).at(new_y);

                q.push({new_cost, {new_x, new_y}});
            }
        }
    }

    throw runtime_error(NO_PATH_FOUND_MESSAGE);
}
