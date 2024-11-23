#include "bfs.hpp"

Path bfs(matrix<double> &M, coords &init, coords &goal) {
    queue<coords> q;
    matrix<coords> parent(W, vector<coords>(H, UNVISITED));

    q.push({init});

    while (!q.empty()) {
        auto node = q.front();
        q.pop();

        if (node == goal) {
            vector<coords> path = rebuild_path(goal, init, parent);

            double path_cost =
                accumulate(path.begin(), path.end(), 0.0, [&M](double sum, const auto &step) {
                    return sum + M.at(step.fi).at(step.se);
                });

            return make_pair(path, path_cost);
        }

        int x = node.fi;
        int y = node.se;

        for (const auto &[dx, dy] : DIRECTIONS) {
            int new_x = x + dx;
            int new_y = y + dy;

            if (is_within_bounds(new_x, new_y) && M.at(new_x).at(new_y) != INF &&
                parent.at(new_x).at(new_y) == UNVISITED) {
                parent.at(new_x).at(new_y) = {x, y};

                q.emplace(new_x, new_y);
            }
        }
    }

    throw runtime_error(NO_PATH_FOUND_MESSAGE);
}
