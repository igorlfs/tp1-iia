#pragma once

#include "common.hpp"

Path ids(matrix<double> &M, coords &init, coords &goal);

optional<Path> dls(matrix<double> &M, coords &init, coords &goal, int max_depth);
