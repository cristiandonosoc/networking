all:
	g++ -g --std=c++11 main.cpp src/address.cpp src/socket.cpp src/platform/socket_linux.cpp
