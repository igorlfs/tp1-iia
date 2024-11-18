#include "bfs.hpp"
#include "ids.hpp"
#include "ucs.hpp"
#include <cassert>
#include <sstream>

constexpr short NUM_ARGS = 7;

map<char, double> terrain_cost_map = {{'.', 1.0}, {';', 1.5}, {'+', 2.5}, {'x', 6.0}, {'@', INF}};

int W, H;

matrix read_matrix(ifstream &input_file) {
    string line;
    getline(input_file, line);

    {
        stringstream stream(line);
        stream >> W >> H;
    }

    matrix M(W, vector<double>(H));

    char c = 0;
    for (int i = 0; getline(input_file, line) and i < H; ++i) {
        stringstream stream(line);
        for (int j = 0; j < W; ++j) {
            stream >> c;
            M.at(j).at(i) = terrain_cost_map[c];
        }
    }

    return M;
}

void print_path(Path &path) {
    cout << fixed << showpoint << setprecision(1) << path.se;
    for (const auto &cell : path.fi) {
        cout << " (" << cell.fi << ", " << cell.se << ")";
    }
    cout << '\n';
}

int main(int argc, char *argv[]) {
    assert(argc == NUM_ARGS);

    ifstream input_file(argv[1]);

    matrix M = read_matrix(input_file);

    coords init = {atoi(argv[3]), atoi(argv[4])};
    assert(init.fi < W && init.se < H);
    coords goal = {atoi(argv[5]), atoi(argv[6])};
    assert(goal.fi < W && goal.se < H);

    string algorithm = argv[2];

    Path path;
    if (algorithm == "BFS") {
        path = bfs(M, init, goal);
    } else if (algorithm == "IDS") {
        path = ids(M, init, goal);
    } else if (algorithm == "UCS") {
        path = ucs(M, init, goal);
    }
    print_path(path);

    return 0;
}
