#ifndef PLATFORM_SOCKET_LINUX_CPP
#define PLATFORM_SOCKET_LINUX_CPP

#include "socket_linux.hpp"
#include "../common_types.hpp"
#include "../address.hpp"

#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>

#include <iostream>
#include <unistd.h>

bool32 Platform::gSocketInitialized = 0;

bool32 Platform::InitializeSockets()
{
    gSocketInitialized = true;
    return true;
}

void Platform::ShutdownSockets()
{
}

int32 Platform::StartSocket(uint16 port)
{
    int32 handle = socket(AF_INET,
                          SOCK_DGRAM,
                          IPPROTO_UDP);
    if (handle <= 0)
    {
        std::cout << "Failed to create socket" 
                  << std::endl;
        return 0;
    }

    sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons((uint16)port);

    int nonBlocking = 1;
    if (fcntl(handle, F_SETFL,
                      O_NONBLOCK,
                      nonBlocking) == -1)
    {
        std::cout << "Failed to set non-blocking" 
                  << std::endl;
        close(handle);
        return 0;
    }

    if (bind(handle, (const sockaddr*)&address, sizeof(sockaddr_in)) < 0)
    {
        std::cout << "Failed to bind socket" 
                  << std::endl;
        close(handle);
        return 0;
    }

    return handle;
}

void Platform::CloseSocket(int32 handle)
{
    close(handle);
}

bool32 Platform::Send(int handle, 
                      const Address& dest,
                      const void *data,
                      int32 size)
{
    // TODO(Cristian): Should this be in the address class?
    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(dest.GetAddress());
    addr.sin_port = htons(dest.GetPort());

    int sent_bytes = sendto(handle,
                            data,
                            size,
                            0,
                            (sockaddr *)&addr,
                            sizeof(sockaddr_in));

    if (sent_bytes == -1)
    {
        perror(0);
    }
    if (sent_bytes != size)
    {
        printf("Failed to send packet\n");
        return false;
    }

    return true;
}

int32 Platform::Receive(int32 handle, 
                        Address& sender,
                        void *buffer, 
                        int32 bufferSize)
{
    sockaddr_in from;
    socklen_t fromLength = sizeof(from);

    int32 bytes = recvfrom(handle,
                           buffer,
                           bufferSize,
                           0,
                           (sockaddr *)&from,
                           &fromLength);

    if (bytes <= 0) { return bytes; }

    uint32 fromAddress = ntohl(from.sin_addr.s_addr);
    uint16 fromPort = ntohl(from.sin_addr.s_addr);
    sender = Address(fromAddress, fromPort);

    return bytes;
}

#endif
