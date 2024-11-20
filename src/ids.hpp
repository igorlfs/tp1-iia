#pragma once

#include "common.hpp"

Path ids(matrix &M, coords &init, coords &goal);

optional<Path> dls(matrix &M, coords &init, coords &goal, int max_depth);
