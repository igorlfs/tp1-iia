CXX=clang++
CXXFLAGS=-std=c++20 -glldb -fstandalone-debug -Wall -Wextra

EXE=bin
EXE_TEST=test

COMMON_SRC_FILES=src/ids.cpp src/bfs.cpp src/ucs.cpp
SRC_FILES=$(COMMON_SRC_FILES) src/main.cpp
TEST_FILES=src/bfs_test.cpp src/ucs_test.cpp src/ids_test.cpp
TEST_SRC_FILES=$(COMMON_SRC_FILES) $(TEST_FILES) src/test.cpp

all: build

build:
	$(CXX) $(CXXFLAGS) -o $(EXE) $(SRC_FILES)

test:
	$(CXX) $(CXXFLAGS) -o $(EXE_TEST) -lgtest $(TEST_SRC_FILES)

clean:
	rm $(EXE_TEST) $(EXE)

fast:
	$(CXX) -O3 -o $(EXE) $(SRC_FILES)

.PHONY: all build clean test fast
