CXX := g++
CXXFLAGS := -std=c++20 -Wall -Wextra -Wno-unused-parameter -MMD -MP
CPPFLAGS := -Ilib/quickjs -Isrc -Isrc/ptrace -Isrc/core -Isrc/Logger -Isrc/JSEngine -Isrc/bindings
LDFLAGS :=
LDLIBS := lib/quickjs/libquickjs.a -ldl -lm -pthread

TARGET := build/main
SRC_DIR := src
BUILD_DIR := build
OBJ_DIR := $(BUILD_DIR)/obj
QUICKJS_DIR := lib/quickjs

CPP_SRCS := $(shell find $(SRC_DIR) -type f -name '*.cpp' | sort)
OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(CPP_SRCS))
DEPS := $(OBJS:.o=.d)

.PHONY: all clean run

all: $(TARGET)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(OBJ_DIR): | $(BUILD_DIR)
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

$(TARGET): $(OBJS) $(QUICKJS_DIR)/libquickjs.a | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(OBJS) $(LDFLAGS) $(LDLIBS) -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -rf $(BUILD_DIR)

-include $(DEPS)