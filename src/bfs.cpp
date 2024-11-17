#include "bfs.hpp"

Path bfs(matrix &M, coords &init, coords &goal) {
    vector<vector<bool>> visited(W, vector<bool>(H));
    vector<vector<coords>> parent(W, vector<coords>(H, {-1, -1}));
    queue<coords> q;

    q.push(init);

    visited.at(init.fi).at(init.se) = true;

    while (!q.empty()) {
        coords current = q.front();
        q.pop();

        if (current == goal) {
            vector<coords> path;
            double cost = 0.0;
            coords step = goal;
            while (step != init) {
                cost += M.at(step.fi).at(step.se);
                path.push_back(step);
                step = parent.at(step.fi).at(step.se);
            }
            path.push_back(init);

            reverse(path.begin(), path.end());

            return make_pair(path, cost);
        }

        for (const auto &[dx, dy] : DIRECTIONS) {
            int new_x = current.fi + dx;
            int new_y = current.se + dy;

            if (is_within_bounds(new_x, new_y) && !visited.at(new_x).at(new_y) &&
                M.at(new_x).at(new_y) != INF) {
                visited.at(new_x).at(new_y) = true;
                q.emplace(new_x, new_y);
                parent.at(new_x).at(new_y) = current;
            }
        }
    }

    cerr << "A path should always exist\n";
    exit(1);
}
