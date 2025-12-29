CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -g -Isrc -MMD -MP 

# Incluindo como sistema pra suprimir as warnings da raygui
INCLUDES = \
    -isystem deps/include

ifeq ($(OS), Windows_NT)
	LDFLAGS = \
    	-L ./deps/lib/windows

	LDLIBS = -lraylib -lgdi32 -lwinmm
else
	LDFLAGS = \
    	-L ./deps/lib

	LDLIBS = ./deps/lib/libraylib.a
endif

SRC_DIR := src
BUILD_DIR := build

SRC := $(shell find $(SRC_DIR) -name "*.cpp")
OBJ := $(SRC:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)
DEP := $(OBJ:.o=.d)

TARGET := Renderer

all: $(BUILD_DIR)/$(TARGET)

$(BUILD_DIR)/$(TARGET): $(OBJ)
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(INCLUDES) -o $@ $(OBJ) $(LDFLAGS) $(LDLIBS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	@mkdir -p $(dir $@)
	$(CXX) $(INCLUDES) $(CXXFLAGS) -c $< -o $@

-include $(DEP)

run:
	build/Renderer

clean:
	rm -f $(OBJ) $(DEP) $(BUILD_DIR)/$(TARGET)