#pragma once

#include "common.hpp"

vector<coords> ids(matrix<double> &M, coords &init, coords &goal);

optional<vector<coords>> dls(matrix<double> &M, coords &init, coords &goal, int max_depth);
