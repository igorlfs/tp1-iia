#include "greedy.hpp"

using State = pair<int, coords>; // {heuristic, coords}

Path greedy(matrix<double> &M, coords &init, coords &goal) {
    matrix<coords> parent(W, vector<coords>(H, UNVISITED));
    priority_queue<State, vector<State>, greater<>> pq;

    pq.emplace(manhattan_distance(init, goal), init);

    while (!pq.empty()) {
        auto [_, current] = pq.top();
        pq.pop();

        int x = current.fi;
        int y = current.se;

        if (current == goal) {
            vector<coords> path = rebuild_path(goal, init, parent);
            double path_cost =
                accumulate(path.begin(), path.end(), 0.0, [&M](double sum, const auto &step) {
                    return sum + M.at(step.fi).at(step.se);
                });

            return {path, path_cost};
        }

        for (const auto &[dx, dy] : DIRECTIONS) {
            int new_x = x + dx;
            int new_y = y + dy;

            if (is_within_bounds(new_x, new_y) && M.at(new_x).at(new_y) != INF &&
                parent.at(new_x).at(new_y) == UNVISITED) {
                parent.at(new_x).at(new_y) = {x, y};

                int heuristic = manhattan_distance({new_x, new_y}, goal);

                pq.emplace(heuristic, make_pair(new_x, new_y));
            }
        }
    }

    throw runtime_error(NO_PATH_FOUND_MESSAGE);
}
