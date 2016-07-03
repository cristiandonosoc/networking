#ifndef ADDRESS_CPP
#define ADDRESS_CPP

#include "address.hpp"
#include <sstream>

// Constructors 

Address::Address() 
{
}

Address::Address(uint8 a, uint8 b, uint8 c, uint8 d, uint16 port) :
    _address((a << 24) | (b << 16) | (c << 8) | d),
    _port(port)
{
}

Address::Address(uint32 address, uint16 port) :
    _address(address),
    _port(port)
{
}

// Getters

uint32 Address::GetAddress() const
{
    return _address;
}

uint8 Address::GetA() const
{
    return (uint8)(_address >> 24);
}

uint8 Address::GetB() const
{
    return (uint8)((_address >> 16) & 0xFF);
}

uint8 Address::GetC() const
{
    return (uint8)((_address >> 8) & 0xFF);
}

uint8 Address::GetD() const
{
    return (uint8)(_address);
}

uint16 Address::GetPort() const
{
    return _port;
}

void Address::SetPort(uint16 port)
{
    _port = port;
}


#include <iostream>
std::string Address::ToString() const
{
    std::ostringstream output;
    output << (uint32)GetA() << "."
           << (uint32)GetB() << "."
           << (uint32)GetC() << "."
           << (uint32)GetD() << ":"
           << GetPort();
    return output.str();
}

#endif
