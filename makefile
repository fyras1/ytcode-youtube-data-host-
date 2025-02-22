# Compiler
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -Iinc `pkg-config --cflags gtk+-3.0`

# Directories
SRC_DIR = src
BUILD_DIR = build

# Sources and Targets
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRCS))
TARGET = $(BUILD_DIR)/app

# Linking Flags
LDFLAGS = `pkg-config --libs gtk+-3.0`

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean
