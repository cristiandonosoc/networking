#include "socket.hpp"
#include "utils.hpp"

#include <string>
#include <iostream>
#include <vector>
#include <sstream>

#include <unistd.h>

#define PORT 30001

int main(int, char **)
{
    Platform::InitializeSockets();

    Socket socket;
    if (!socket.Open(PORT))
    {
        std::cout << "COULD NOT OPEN SOCKET ON PORT: "
                  << PORT << std::endl;
        return 1;
    }

    // We get the target IP
    std::string ipString;
    std::cout << "Insert IP address: ";
    std::cin >> ipString;

    Address targetAddress;
    if (!utils::ObtainAddressFromString(ipString, targetAddress))
    {
        return 1;
    }

    Address senderAddress;
    std::string message;
    while (true)
    {
        message.clear();
        std::cout << "Insert message: ";
        std::cin >> message;

        if (!socket.Send(targetAddress, message.c_str(), message.length()))
        {
            return 1;
        }
        else
        {
            std::cout << "SENT " << message << std::endl;
        }

        sleep(1);
    }

    return 0;
}


