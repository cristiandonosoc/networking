#ifndef UTILS_HPP
#define UTILS_HPP

#include "common_types.hpp"
#include "address.hpp"
#include <string>
#include <vector>

namespace utils
{

void StringSplit(const std::string& input, const char delim,
                 std::vector<std::string>& output);

bool32 ObtainAddressFromString(const std::string& input,
                                Address& output);

};

#endif

