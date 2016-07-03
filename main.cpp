// platform detection

#include "src/socket.hpp"

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

    Address targetAddress(127, 0, 0, 1, PORT);

    std::string data("DATA");

    Address senderAddress;

    int programCounter = 0;
    int counter = 4;
    while (true)
    {
        printf("PASS\n");
        ++counter;
        ++programCounter;

        if (programCounter == 30)
        {
            break;
        }

        if (counter == 5)
        {
            counter = 0;

            if (!socket.Send(targetAddress, data.c_str(), data.length()))
            {
                return 1;
            }
        }

        int32 readBytes = socket.Receive(senderAddress, packetData, maxPacketSize);

        if (readBytes > 0)
        {
            std::cout << "RECEIVED " << readBytes 
                      << " BYTES: " << packetData
                      << std::endl;
        }

        sleep(1);
    }

    return 0;
}
