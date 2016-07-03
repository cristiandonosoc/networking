#include "socket.hpp"

#include <string>
#include <iostream>

#include <unistd.h>

#define PORT 30000

int main(int, char **)
{
    Platform::InitializeSockets();

    Socket socket;
    if (!socket.Open(PORT))
    {
        std::cout << "COULD NOT OPEN SOCKET ON PORT: "
                  << PORT << std::endl;
        return 1;
    }

    int maxPacketSize = 256;
    char packetData[maxPacketSize];

    Address senderAddress;
    while (true)
    {
        int32 readBytes = socket.Receive(senderAddress, packetData, maxPacketSize);
        if (readBytes > 0)
        {
            packetData[readBytes] = '\0';
            std::cout << "RECEIVED " << readBytes 
                      << " BYTES: " << packetData
                      << " FROM: " << senderAddress.ToString()
                      << std::endl;
        }

        usleep(100); // ~10 FPS
    }

    return 0;
}
