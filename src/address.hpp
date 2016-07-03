#ifndef ADDRESS_HPP
#define ADDRESS_HPP

#include "common_types.hpp"
#include <string>

class Address
{
public:
    Address();
    Address(uint8 a, uint8 b, uint8 c, uint8 d, uint16 port);
    Address(uint32 address, uint16 port);

public:
    uint32 GetAddress() const;
    uint8 GetA() const;
    uint8 GetB() const;
    uint8 GetC() const;
    uint8 GetD() const;
    uint16 GetPort() const;
    void SetPort(uint16 port);
    std::string ToString() const;

private:

private:
    uint32 _address;
    uint16 _port;
};

#endif
