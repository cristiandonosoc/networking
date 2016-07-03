#ifndef UTILS_CPP
#define UTILS_CPP

#include "utils.hpp"
#include <sstream>
#include <iostream>

void utils::StringSplit(const std::string& input, const char delim,
                 std::vector<std::string>& output)
{
    std::stringstream ss(input);
    std::string item;
    while (std::getline(ss, item, delim))
    {
        output.push_back(item);
    }
}

bool32 utils::ObtainAddressFromString(const std::string& input,
                                Address& output)
{
    // We parse the ip string
    std::vector<std::string> sepIp;
    StringSplit(input, '.', sepIp);

    if (sepIp.size() != 4)
    {
        std::cout << "COULD NOT PARSE INPUT IP STRING: "
                  << input << std::endl;
        return false;
    }

    int32 elem[4];
    std::vector<std::string>::const_iterator iter;
    int index = 0;
    for (iter = sepIp.cbegin(), index = 0;
         iter != sepIp.cend();
         ++iter, ++index)
    {
        int32 parsedInt = std::stoi(*iter);
        elem[index] = parsedInt;
    }

    output = Address(elem[0], elem[1], elem[2], elem[3], 30000);
    return true;
}

#endif
