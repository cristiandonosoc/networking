CXX=g++
DEPS=src/address.cpp src/socket.cpp src/platform/socket_linux.cpp src/utils.cpp
OBJ_DIR=obj

BIN_DIR=bin

FLAGS=-g --std=c++11

INCLUDE=-I /home/cristiandonosoc/Dev/SDL2-2.0.4/include
LIB=-L /home/cristiandonosoc/Dev/SDL2-2.0.4/lib

all: server client

server: $(BIN_DIR)
	$(CXX) $(FLAGS) src/server.cpp $(DEPS) -o $(BIN_DIR)/server

client: $(BIN_DIR)
	$(CXX) $(FLAGS) src/client.cpp $(DEPS) -o $(BIN_DIR)/client

sdl: $(BIN_DIR)
	$(CXX) $(FLAGS) $(INCLUDE) $(LIB) sdl.cpp -o $(BIN_DIR)/sdl


$(BIN_DIR):
	mkdir -p $(BIN_DIR)
