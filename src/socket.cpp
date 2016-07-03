#ifndef SOCKET_CPP
#define SOCKET_CPP

#include "socket.hpp"
#include "common_types.hpp"
#include "address.hpp"

#include <iostream>

// Constructors

Socket::Socket() :
    _handle(0),
    _open(false),
    _port(0)
{
    ASSERT(Platform::gSocketInitialized);
}

// Destructors

Socket::~Socket()
{
    if (_handle != 0)
    {
        Platform::CloseSocket(_handle);
    }
}

bool32 Socket::Open(uint16 port)
{
    _handle = Platform::StartSocket(port);
    if (_handle > 0)
    {
        _port = port;
        _open = true;
    }

    return _open;
}

bool32 Socket::IsOpen() const
{
    return _open;
}

bool32 Socket::Send(const Address& dest,
                    const void *data,
                    int32 size)
{
    if (!_open)
    {
        std::cout << "SOCKET MUST BE OPENED BEFORE USING"
                  << std::endl;
        return false;
    }

    bool32 result = Platform::Send(_handle, dest, data, size);
    return result;
}

int32 Socket::Receive(Address& sender,
                      void *buffer,
                      int32 bufferSize)
{
    if (!_open)
    {
        std::cout << "SOCKET MUST BE OPENED BEFORE USING"
                  << std::endl;
        return false;
    }

    int32 bytes = Platform::Receive(_handle,
                                    sender,
                                    buffer,
                                    bufferSize);
    return bytes;
}

#endif
