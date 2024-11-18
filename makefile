CXX=clang++
CXXFLAGS=-std=c++20 -glldb -fstandalone-debug -Wall -Wextra

EXE=bin
EXE_TEST=test

COMMON_SRC_FILES=src/ids.cpp src/bfs.cpp src/ucs.cpp
SRC_FILES=$(COMMON_SRC_FILES) src/main.cpp
TEST_SRC_FILES=$(COMMON_SRC_FILES) src/test_algorithms.cpp

all: build

build:
	$(CXX) $(CXXFLAGS) -o $(EXE) $(SRC_FILES)

test:
	$(CXX) $(CXXFLAGS) -o $(EXE_TEST) -lgtest $(TEST_SRC_FILES)

ci:
	g++ -std=c++20 -o $(EXE_TEST) -lgtest $(TEST_SRC_FILES)

clean:
	rm $(EXE_TEST) $(EXE)

.PHONY: all build clean test ci
