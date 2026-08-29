CXX := g++
CXXFLAGS := -std=c++20 -Wall -Wextra -O2 -w

SRC_DIR := src
INC_DIR := h
BASE_NAME := socialGraph

CXXFLAGS += -I$(INC_DIR)

SRCS := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(SRCS:.cpp=.o)

# check os
ifeq ($(OS),Windows_NT)
	RM := del /Q /F
	FIX_PATH = $(subst /,\,$1)
	TARGET := $(BASE_NAME).exe
else
	RM := rm -f
	FIX_PATH = $1
	TARGET := $(BASE_NAME)
endif

# build rules
.PHONY: all clean

all: $(TARGET)

# linking
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(SRC_DIR)/*.o

# compiling
$(SRC_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# clean
clean:
	$(RM) $(call FIX_PATH,$(OBJS)) $(TARGET)