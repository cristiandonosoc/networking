#ifndef SOCKET_CPP
#define SOCKET_CPP

#include "socket.hpp"
#include "common_types.hpp"
#include "address.hpp"

#include "platform/identify.hpp"
#if PLATFORM == PLATFORM_UNIX
#include "platform/socket_linux.cpp"
#endif

// Constructors

Socket::Socket() :
    _handle(0),
    _open(false)
{
    ASSERT(Platform::gSocketInitialized);
}

// Destructors

Socket::~Socket()
{
    if (_handle != 0)
    {
        close(_handle);
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
}

bool32 Socket::IsOpen() const
{
    return _open;
}

bool32 Socket::Send(const Address& dest,
                    const void *data,
                    int32 size)
{
    bool32 result = Platform::Send(_handle, dest, data, size);
    return result;
}

int32 Socket::Receive(Address& sender,
                      void *buffer,
                      int32 bufferSize)
{
    int32 bytes = Platform::Receive(_handle,
                                    sender,
                                    buffer,
                                    bufferSize);
    return bytes;
}

#endif
