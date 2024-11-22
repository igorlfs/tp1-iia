#include "astar.hpp"

using State = pair<double, coords>; // {g + h, coords}

Path astar(matrix<double> &M, coords &init, coords &goal) {
    priority_queue<State, vector<State>, greater<>> pq;
    vector<vector<coords>> parent(W, vector<coords>(H, UNVISITED));
    vector<vector<double>> cost(W, vector<double>(H, INF));

    pq.emplace(0.0 + manhattan_distance(init, goal), init);
    cost.at(init.fi).at(init.se) = 0.0;

    while (!pq.empty()) {
        auto [f, current] = pq.top(); // f = g + h
        pq.pop();

        if (current == goal) {
            vector<coords> path = rebuild_path(goal, init, parent);

            return {path, cost.at(goal.fi).at(goal.se)};
        }

        int x = current.fi;
        int y = current.se;

        for (const auto &[dx, dy] : DIRECTIONS) {
            int new_x = x + dx;
            int new_y = y + dy;

            if (is_within_bounds(new_x, new_y) && M.at(new_x).at(new_y) != INF) {
                double new_cost = cost[x][y] + M[new_x][new_y];

                if (new_cost < cost.at(new_x).at(new_y)) {
                    cost.at(new_x).at(new_y) = new_cost;
                    parent.at(new_x).at(new_y) = {x, y};

                    double h = manhattan_distance({new_x, new_y}, goal);
                    pq.push({new_cost + h, {new_x, new_y}});
                }
            }
        }
    }

    throw runtime_error(NO_PATH_FOUND_MESSAGE);
}
