// platform detection

#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

bool InitializeSockets()
{
    return true;
}

void ShutdownSockets()
{
}

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

bool StartSocket(int &handle)
{
    handle = socket(AF_INET,
                        SOCK_DGRAM,
                        IPPROTO_UDP);
    if (handle <= 0)
    {
        printf("failed to create socket!\n");
        return false;
    }

    sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons((unsigned short)PORT);

    if (bind(handle, (const sockaddr*)&address, sizeof(sockaddr_in)) < 0)
    {
        printf("failed to bind socket!\n");
        return false;
    }

    return true;
}

bool SendPacket(int handle, sockaddr_in& address)
{
    char packet_data[] = "DATA";
    int packet_size = (int)(strlen(packet_data) + 1);
    int sent_bytes = sendto(handle,
                            (const char*)packet_data,
                            packet_size,
                            0,
                            (sockaddr *)&address,
                            sizeof(sockaddr_in));

    printf("SENDING PACKET (SEND: %d)\n", sent_bytes);
    if (sent_bytes == -1)
    {
        perror(0);
    }
    if (sent_bytes != packet_size)
    {
        printf("Failed to send packet\n");
        return false;
    }

    return true;
}

bool ReceivePacket(int handle, char *packetBuffer, int packetBufferSize)
{
    sockaddr_in from;
    socklen_t fromLength = sizeof(from);

    int bytes = recvfrom(handle,
                         packetBuffer,
                         packetBufferSize,
                         0,
                         (sockaddr *)&from,
                         &fromLength);

    if (bytes <= 0) { return false; }

    unsigned int fromAddress = ntohl(from.sin_addr.s_addr);
    unsigned int fromPort = ntohl(from.sin_addr.s_addr);

    printf("Received from %d:%d", fromAddress, fromPort);
    return true;
}

sockaddr_in CreateSocketAddress(int a, int b, int c, int d, int port)
{
    unsigned int address = (a << 24) |
                           (b << 16) |
                           (c <<  8) |
                           (d <<  0);
    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(address);
    addr.sin_port = htons(port);

    return addr;
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
