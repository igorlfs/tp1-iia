#include "ucs.hpp"

using State = pair<double, pair<coords, vector<coords>>>;

Path ucs(matrix &M, coords &init, coords &goal) {
    priority_queue<State, vector<State>, greater<>> pq;
    set<coords> visited;

    pq.push({0.0, {init, {init}}});

    while (!pq.empty()) {
        auto [current_cost, state] = pq.top();
        auto [current_coords, current_path] = state;
        pq.pop();

        if (visited.count(current_coords) != 0) {
            continue;
        }
        visited.insert(current_coords);

        if (current_coords == goal) {
            return {current_path, current_cost};
        }

        int x = current_coords.fi;
        int y = current_coords.se;

        for (const auto &[dx, dy] : DIRECTIONS) {
            int new_x = x + dx;
            int new_y = y + dy;

            if (is_within_bounds(new_x, new_y) && M.at(new_x).at(new_y) != INF) {
                double new_cost = current_cost + M.at(new_x).at(new_y);
                vector<coords> new_path = current_path;
                new_path.emplace_back(new_x, new_y);

                pq.push({new_cost, {{new_x, new_y}, new_path}});
            }
        }
    }

    cerr << "A path should always exist\n";
    exit(1);
}
