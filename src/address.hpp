#ifndef ADDRESS_HPP
#define ADDRESS_HPP

#include "common_types.hpp"

class Address
{
public:
    Address();
    Address(uint8 a, uint8 b, uint8 c, uint8 d, uint16 port);
    Address(uint32 address, uint16 port);

public:
    uint32 GetAddress() const;
    uint8 GetA() const { return (uint8)(_address >> 24); }
    uint8 GetB() const { return (uint8)((_address >> 16) & 0xFF); }
    uint8 GetC() const { return (uint8)((_address >>  8) & 0xFF); }
    uint8 GetD() const { return (uint8)(_address & 0xFF); }
    uint16 GetPort() const { return _port; }

private:
    uint32 _address;
    uint16 _port;
}

#endif
