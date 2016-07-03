#ifndef PLATFORM_SOCKET_LINUX_HPP
#define PLATFORM_SOCKET_LINUX_HPP

#include "../common_types.hpp"
#include "../address.hpp"

namespace Platform
{
extern bool32 gSocketInitialized;

bool32 InitializeSockets();

void ShutdownSockets();

int32 StartSocket(uint16 port);

void CloseSocket(int32 handle);

bool32 Send(int handle,
            const Address& dest,
            const void *data,
            int32 size);

int32 Receive(int32 handle,
              Address& sender,
              void *buffer,
              int32 bufferSize);

}

#endif
