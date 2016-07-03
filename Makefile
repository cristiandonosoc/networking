CXX=g++
DEPS=src/address.cpp src/socket.cpp src/platform/socket_linux.cpp src/utils.cpp
OBJ_DIR=obj

BIN_DIR=bin

FLAGS=-g --std=c++11

all: server client

server: $(BIN_DIR)
	$(CXX) $(FLAGS) src/server.cpp $(DEPS) -o $(BIN_DIR)/server

client: $(BIN_DIR)
	$(CXX) $(FLAGS) src/client.cpp $(DEPS) -o $(BIN_DIR)/client


$(BIN_DIR):
	mkdir -p $(BIN_DIR)
