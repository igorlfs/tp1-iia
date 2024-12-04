#include "ucs.hpp"

using State = pair<double, coords>;

Path ucs(matrix<double> &M, coords &init, coords &goal) {
    priority_queue<State, vector<State>, greater<>> pq;
    matrix<double> cost(W, vector<double>(H, INF));
    matrix<coords> parent(W, vector<coords>(H, UNVISITED));

    pq.push({0.0, {init}});
    cost.at(init.fi).at(init.se) = 0.0;

    while (!pq.empty()) {
        auto [current_cost, node] = pq.top();
        pq.pop();

        if (node == goal) {
            vector<coords> path = rebuild_path(goal, init, parent);

            return {path, current_cost};
        }

        int x = node.fi;
        int y = node.se;

        for (const auto &[dx, dy] : DIRECTIONS) {
            int new_x = x + dx;
            int new_y = y + dy;

            if (is_within_bounds(new_x, new_y) && M.at(new_x).at(new_y) != INF &&
                parent.at(new_x).at(new_y) == UNVISITED) {
                double new_cost = current_cost + M.at(new_x).at(new_y);

                if (new_cost < cost.at(new_x).at(new_y)) {
                    cost.at(new_x).at(new_y) = new_cost;
                    parent.at(new_x).at(new_y) = {x, y};
                    pq.emplace(new_cost, make_pair(new_x, new_y));
                }
            }
        }
    }

    throw runtime_error(NO_PATH_FOUND_MESSAGE);
}
