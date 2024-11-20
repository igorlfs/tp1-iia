#include "ucs.hpp"

Path ucs(matrix<double> &M, coords &init, coords &goal) {
    priority_queue<State, vector<State>, greater<>> pq;
    set<coords> visited;
    matrix<double> cost(W, vector<double>(H, INF));
    matrix<coords> parent(W, vector<coords>(H, {-1, -1}));

    pq.push({0.0, {init}});

    while (!pq.empty()) {
        auto [current_cost, current_coords] = pq.top();
        pq.pop();

        if (visited.count(current_coords) != 0) {
            continue;
        }
        visited.insert(current_coords);

        if (current_coords == goal) {
            vector<coords> path = rebuild_path(goal, init, parent);

            return make_pair(path, current_cost);
        }

        int x = current_coords.fi;
        int y = current_coords.se;

        for (const auto &[dx, dy] : DIRECTIONS) {
            int new_x = x + dx;
            int new_y = y + dy;

            if (is_within_bounds(new_x, new_y) && M.at(new_x).at(new_y) != INF) {
                double new_cost = current_cost + M.at(new_x).at(new_y);

                if (new_cost < cost[new_x][new_y]) {
                    cost[new_x][new_y] = new_cost;
                    parent[new_x][new_y] = {x, y};
                    pq.emplace(new_cost, make_pair(new_x, new_y));
                }
            }
        }
    }

    throw runtime_error(NO_PATH_FOUND_MESSAGE);
}
