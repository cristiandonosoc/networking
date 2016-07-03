CXX=g++
OBJ=main.cpp src/address.cpp src/socket.cpp src/platform/socket_linux.cpp
OBJ_DIR=obj

BIN=socket
BIN_DIR=bin

FLAGS=-g --std=c++11


all: $(BIN_DIR)
	$(CXX) $(FLAGS) $(OBJ) -o $(BIN_DIR)/$(BIN)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)
