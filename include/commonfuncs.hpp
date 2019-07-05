#pragma once

#include <cstdint>
#include <string>
#include <vector>
#include <sstream>
#include <cstring>
#include <fstream>
#include <iostream>
#include <ios>

#include "constants.hpp"

template <class T>
T getSlice(uint64_t word, int start, int end) {
    uint64_t slice = word << (64 - start);
    return (T)(slice >> (64 - (start - end)));
}

std::vector<uint64_t> getLUT(std::string filename);
