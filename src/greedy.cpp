#include "greedy.hpp"

using State = pair<int, coords>; // {heuristic, coords}

vector<coords> greedy(matrix<double> &M, coords &init, coords &goal) {
    matrix<coords> parent(W, vector<coords>(H, UNVISITED));
    priority_queue<State, vector<State>, greater<>> pq;

    pq.emplace(manhattan_distance(init, goal), init);

    while (!pq.empty()) {
        auto [_, node] = pq.top();
        pq.pop();

        if (node == goal) {
            return rebuild_path(goal, init, parent);
        }

        int x = node.fi;
        int y = node.se;

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
