CXX := g++
CXXFLAGS := -std=c++11 # -Wall -Wextra

SRC_DIR := includes
BUILD_DIR := build
BIN_DIR := build/bin
# TESTS_DIR := _tests # make sure this is the correct directory before uncommenting

# GTESTINCL := -I/usr/include/gtest/
# GTESTLIBS := -lgtest -lgtest_main -lpthread

# HEADERS := $(wildcard $(SRC_DIR)/**/*.h)
# HEADER_DIRS := $(dir $(HEADERS))
# HEADERINCL := $(addprefix -I, $(HEADER_DIRS))
# HEADERINCL := -Iincludes

SRCS := $(wildcard $(SRC_DIR)/**/*.cpp)
OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRCS))
OBJS_DIRS := $(dir $(OBJS))

# TEST_SRCS := $(wildcard $(TESTS_DIR)/*.cpp)
# TEST_OBJS := $(patsubst $(TESTS_DIR)%.cpp,$(BUILD_DIR)/$(TESTS_DIR)/%.o,$(TEST_SRCS))
# TEST_OBJS_DIRS := $(dir $(TEST_OBJS))

EXEC := $(BIN_DIR)/main
# TESTS_EXEC := $(BIN_DIR)/tests

all: $(EXEC)

$(EXEC): $(BUILD_DIR)/main.o $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(BUILD_DIR)/main.o: main.cpp build
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp build
	$(CXX) $(CXXFLAGS) -c $< -o $@

# tests: $(TESTS_EXEC)

# $(TESTS_EXEC): $(OBJS) $(TEST_OBJS)
# 	$(CXX) $(CXXFLAGS) $(GTEST_INCL) $(HEADER_INCL) $^ -o $@ $(GTEST_LIBS)

# $(BUILD_DIR)/$(TESTS_DIR)/%.o: $(TESTS_DIR)/%.cpp build
# 	$(CXX) $(CXXFLAGS) $(GTEST_INCL) $(HEADER_INCL) -c $< -o $@ $(GTEST_LIBS)

build:
	@mkdir -p $(BIN_DIR)
	@mkdir -p $(OBJS_DIRS)
# @mkdir -p $(TEST_OBJS_DIRS)

clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)

.PHONY: all tests build clean