CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -Wpedantic -Werror -Wshadow -Wconversion -Wsign-conversion -Wnull-dereference -Wold-style-cast -Woverloaded-virtual -Wdouble-promotion -Wformat=2 -Isrc -pthread -fsanitize=address,undefined

# Directories
SRC_DIR = src
TIMER_DIR = src/timer
BUILD_DIR = build
I3_DIR = src/frontends/i3
CLI_DIR = src/frontends/cli

# Create build directory if it doesn't exist
$(shell mkdir -p $(BUILD_DIR) $(BUILD_DIR)/i3 $(BUILD_DIR)/cli $(BUILD_DIR)/timer)

# Core source files (timer logic)
CORE_SRCS = $(wildcard $(TIMER_DIR)/*.cpp)
CORE_OBJS = $(CORE_SRCS:$(TIMER_DIR)/%.cpp=$(BUILD_DIR)/timer/%.o)

# Frontend source files
I3_SRCS = $(I3_DIR)/main_i3.cpp $(I3_DIR)/utils.cpp
I3_OBJS = $(I3_SRCS:$(I3_DIR)/%.cpp=$(BUILD_DIR)/i3/%.o)

CLI_SRCS = $(CLI_DIR)/main_cli.cpp
CLI_OBJS = $(CLI_SRCS:$(CLI_DIR)/%.cpp=$(BUILD_DIR)/cli/%.o)

# Targets
I3_TARGET = $(BUILD_DIR)/timebox-i3
CLI_TARGET = $(BUILD_DIR)/timebox-cli

# Default target (build both frontends)
all: $(I3_TARGET) $(CLI_TARGET)

# Individual frontend targets
i3: $(I3_TARGET)
cli: $(CLI_TARGET)

# i3 target
$(I3_TARGET): $(CORE_OBJS) $(I3_OBJS)
	$(CXX) $(CXXFLAGS) $(CORE_OBJS) $(I3_OBJS) -o $@

# cli target (interactive terminal)
$(CLI_TARGET): $(CORE_OBJS) $(CLI_OBJS)
	$(CXX) $(CXXFLAGS) $(CORE_OBJS) $(CLI_OBJS) -o $@

# Compile core source files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compile i3 frontend source files
$(BUILD_DIR)/i3/%.o: $(I3_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -I$(I3_DIR) -c $< -o $@

# Compile cli frontend source files
$(BUILD_DIR)/cli/%.o: $(CLI_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -I$(CLI_DIR) -c $< -o $@

# Clean build artifacts
clean:
	rm -rf $(BUILD_DIR)

# Phony targets
.PHONY: all i3 cli clean