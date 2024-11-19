#include "bfs.hpp"

Path bfs(matrix &M, coords &init, coords &goal) {
    vector<vector<bool>> visited(W, vector<bool>(H));
    queue<State> q;

    q.push({0.0, {init, {init}}});

    visited.at(init.fi).at(init.se) = true;

    while (!q.empty()) {
        auto [current_cost, state] = q.front();
        auto [current_coords, current_path] = state;
        q.pop();

        if (current_coords == goal) {
            return {current_path, current_cost};
        }

        int x = current_coords.fi;
        int y = current_coords.se;

        for (const auto &[dx, dy] : DIRECTIONS) {
            int new_x = x + dx;
            int new_y = y + dy;

            if (is_within_bounds(new_x, new_y) && !visited.at(new_x).at(new_y) &&
                M.at(new_x).at(new_y) != INF) {
                visited.at(new_x).at(new_y) = true;

                double new_cost = current_cost + M.at(new_x).at(new_y);
                vector<coords> new_path = current_path;

                new_path.emplace_back(new_x, new_y);

                q.push({new_cost, {{new_x, new_y}, new_path}});
            }
        }
    }

    cerr << "A path should always exist\n";
    exit(1);
}
