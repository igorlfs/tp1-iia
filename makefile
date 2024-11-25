# Directories
BUILD_DIR = obj
SRC_DIR = src
LIB_DIR = lib
TEST_DIR = tests

# Compiler
CXX = clang++

# Flags: Compile, more warnings, use C++20, enable debugging symbols and include path
CXXFLAGS = -c -Wall -Wextra -Wshadow -Wpedantic -std=c++20 -g -fstandalone-debug -I$(LIB_DIR)

# Binaries
TARGET = bin
TESTS = test

# Source
CPP_SOURCE = $(filter-out $(SRC_DIR)/main.cpp, $(wildcard $(SRC_DIR)/*))
CPP_TEST_SOURCE = $(filter-out $(TEST_DIR)/main_test.cpp, $(wildcard $(TEST_DIR)/*))
 
# Headers
HPP_SOURCE = $(wildcard $(LIB_DIR)/*)
 
# Objects
OBJ = $(subst .cpp,.o,$(subst $(SRC_DIR),$(BUILD_DIR),$(CPP_SOURCE)))
TEST_OBJ = $(subst .cpp,.o,$(subst $(TEST_DIR),$(BUILD_DIR),$(CPP_TEST_SOURCE)))
 
# Command used at clean target
RM = rm -rf
 
# Compilation and linking
all: $(BUILD_DIR) $(TARGET)

$(TARGET): $(OBJ) ./$(BUILD_DIR)/main.o
	$(CXX) $^ -o $@
 
./$(BUILD_DIR)/main.o: ./$(SRC_DIR)/main.cpp $(HPP_SOURCE)
	$(CXX) $< $(CXXFLAGS) -o $@

test: $(TESTS)

$(TESTS): $(TEST_OBJ) $(OBJ) ./$(BUILD_DIR)/main_test.o
	$(CXX) $^ -lgtest -o $@
	./$(TESTS)

./$(BUILD_DIR)/main_test.o: ./$(TEST_DIR)/main_test.cpp $(HPP_SOURCE)
	$(CXX) $< $(CXXFLAGS) -o $@

$(BUILD_DIR)/%_test.o: $(TEST_DIR)/%_test.cpp $(LIB_DIR)/%.hpp
	$(CXX) $< $(CXXFLAGS) -o $@

./$(BUILD_DIR)/%.o: ./$(SRC_DIR)/%.cpp ./$(LIB_DIR)/%.hpp ./$(LIB_DIR)/common.hpp
	$(CXX) $< $(CXXFLAGS) -o $@
 
obj:
	@ test -d $(BUILD_DIR) && true || mkdir -p $(BUILD_DIR)
 
clean:
	@ $(RM) ./$(BUILD_DIR)/*.o $(TARGET) $(TESTS) *~
	@ test -d $(BUILD_DIR) && rmdir $(BUILD_DIR) || echo "Nothing to clean"
 
.PHONY: all clean obj test
