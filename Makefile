MAIN_SRC := main.c
TARGET := main

CXX := gcc
BUILD_FLAGS := -Wall -g
LIBS := -lncurses

SRC_PATH := src
BIN_PATH := bin

build: $(SRC_PATH)/$(MAIN_SRC)
	$(CXX) $(SRC_PATH)/$(MAIN_SRC) -o $(BIN_PATH)/$(TARGET) $(BUILD_FLAGS) $(LIBS)

run: $(BIN_PATH)/$(TARGET)
	./$(BIN_PATH)/$(TARGET)
