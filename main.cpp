// platform detection


#include <stdio.h>

#include <string.h>
#include <unistd.h>


#define PORT 30000

bool SetSocketAsNonBlocking(int handle)
{
    int nonBlocking = 1;
    if (fcntl(handle, F_SETFL,
                      O_NONBLOCK,
                      nonBlocking) == -1)
    {
        printf("failed to set non-blocking\n");
        return false;
    }

    return true;
}

int main(int, char **)
{
    InitializeSockets();

    int socketHandle;
    if(!StartSocket(socketHandle))
    {
        return 1;
    }
    if (!SetSocketAsNonBlocking(socketHandle))
    {
        return 1;
    }

    int maxPacketSize = 256;
    char packetData[maxPacketSize];

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

            sockaddr_in targetAddress = CreateSocketAddress(127, 0, 0, 1, 30000);
            if (!SendPacket(socketHandle, targetAddress))
            {
                return 1;
            }
        }

        bool result = ReceivePacket(socketHandle, packetData, maxPacketSize);
        if (result)
        {
            printf("RECEIVED: %s\n", packetData);
        }
        sleep(1);
    }

    close(socketHandle);
    ShutdownSockets();

}
