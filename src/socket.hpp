#ifndef SOCKET_HPP
#define SOCKET_HPP

#include "common_types.hpp"
#include "address.hpp"

class Socket
{
public:
    Socket();
    ~Socket();

    bool32 Open(uint16 port);
    bool32 IsOpen() const;

    bool32 Send(const Address& dest,
                const void *data,
                int32 size);
    int32 Receive(Address& sender,
                  void *buffer,
                  int32 size);

private:
    int32 _handle;
    bool32 _open;
    int16 _port;
};

#endif
