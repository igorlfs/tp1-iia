#include "astar.hpp"
#include "bfs.hpp"
#include "greedy.hpp"
#include "ids.hpp"
#include "ucs.hpp"

constexpr short NUM_ARGS = 7;

int W, H;

using AlgorithmFunc = function<vector<coords>(matrix<double> &, coords &, coords &)>;

static const unordered_map<string, AlgorithmFunc> ALGORITHMS = {
    {"BFS", bfs}, {"IDS", ids}, {"UCS", ucs}, {"Greedy", greedy}, {"Astar", astar}};

static const map<char, double> TERRAIN_COST_MAP = {
    {'.', 1.0}, {';', 1.5}, {'+', 2.5}, {'x', 6.0}, {'@', INF}};

namespace {

matrix<double> read_matrix(ifstream &input_file) {
    string line;
    getline(input_file, line);

    {
        stringstream stream(line);
        stream >> W >> H;
    }

    matrix<double> M(W, vector<double>(H));

    char c = 0;
    for (int i = 0; getline(input_file, line) and i < H; ++i) {
        stringstream stream(line);
        for (int j = 0; j < W; ++j) {
            stream >> c;
            M.at(j).at(i) = TERRAIN_COST_MAP.at(c);
        }
    }

    return M;
}

void print_path(vector<coords> &path, double cost, coords init) {
    cout << fixed << showpoint << setprecision(1) << cost;
    cout << " (" << init.fi << "," << init.se << ")";
    for (const auto &cell : path) {
        cout << " (" << cell.fi << "," << cell.se << ")";
    }
    cout << '\n';
}
} // namespace

int main(int argc, char *argv[]) {
    assert(argc == NUM_ARGS);
    vector<string> args(argv, argv + argc);

    ifstream input_file(args.at(1));

    matrix<double> M = read_matrix(input_file);

    coords init = {stoi(args.at(3)), stoi(args.at(4))};
    assert(init.fi < W && init.se < H);
    coords goal = {stoi(args.at(5)), stoi(args.at(6))};
    assert(goal.fi < W && goal.se < H);

    // Agent can never be at an invalid position
    assert(M.at(init.fi).at(init.se) != INF);
    assert(M.at(goal.fi).at(goal.se) != INF);

    vector<coords> path = ALGORITHMS.at(args.at(2))(M, init, goal);

    double cost = accumulate(path.begin(), path.end(), 0.0, [&M](double sum, const auto &step) {
        return sum + M.at(step.fi).at(step.se);
    });

    print_path(path, cost, init);

    return 0;
}
