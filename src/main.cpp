#include <bits/stdc++.h>
#include <cassert>
#include <sstream>

#define endl '\n'
#define fi first
#define se second

using namespace std;

constexpr int INF = 0x3f3f3f3f;
constexpr short NUM_ARGS = 7;

map<char, double> terrain_cost_map = {{'.', 1.0}, {';', 1.5}, {'+', 2.5}, {'x', 6.0}, {'@', INF}};

using matrix = vector<vector<double>>;
using coords = pair<int, int>;
using Path = pair<vector<coords>, double>;

int W, H;

matrix read_matrix(ifstream &input_file) {
    string line;
    getline(input_file, line);

    {
        stringstream stream(line);
        stream >> W >> H;
    }

    matrix M(H, vector<double>(W));

    char c = 0;
    for (int i = 0; getline(input_file, line) and i < H; ++i) {
        stringstream stream(line);
        for (int j = 0; j < W; ++j) {
            stream >> c;
            M.at(i).at(j) = terrain_cost_map[c];
        }
    }

    return M;
}

bool is_within_bounds(int x, int y) {
    return x >= 0 && x < H && y >= 0 && y < W;
}

Path bfs(matrix &M, coords &init, coords &goal) {
    const vector<coords> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    vector<vector<bool>> visited(H, vector<bool>(W));
    vector<vector<coords>> parent(H, vector<coords>(W, {-1, -1}));
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

        for (const auto &[dx, dy] : directions) {
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

    throw "A path should always exist";
}

void print_path(Path &path) {
    cout << fixed << showpoint << setprecision(1) << path.se;
    for (const auto &cell : path.fi) {
        cout << " (" << cell.fi << ", " << cell.se << ")";
    }
    cout << endl;
}

int main(int argc, char *argv[]) {
    assert(argc == NUM_ARGS);

    ifstream input_file(argv[1]);

    matrix M = read_matrix(input_file);

    coords init = {atoi(argv[4]), atoi(argv[3])};
    assert(init.fi < H && init.se < W);
    coords goal = {atoi(argv[6]), atoi(argv[5])};
    assert(goal.fi < H && goal.se < W);

    string algorithm = argv[2];

    Path path;
    if (algorithm == "BFS") {
        path = bfs(M, init, goal);
    }
    print_path(path);

    return 0;
}
