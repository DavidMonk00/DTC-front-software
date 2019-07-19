/*
Filename: commonfuncs.hpp
Author: David Monk
Institution: Imperial College London

Description: Add description here.
*/

#pragma once

#include <cstdint>
#include <string>
#include <vector>
#include <sstream>
#include <cstring>
#include <fstream>
#include <iostream>
#include <ios>
#include <algorithm>
#include <cctype>
#include <locale>

#include "constants.hpp"

template <class T>
T getSlice(uint64_t word, int start, int end) {
    uint64_t slice = word << (64 - start);
    return (T)(slice >> (64 - (start - end)));
}

std::vector<uint64_t> getLUT(std::string filename, int lines=0);

// trim from start (in place)
static inline void ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
        return !std::isspace(ch);
    }));
}

// trim from end (in place)
static inline void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}

// trim from both ends (in place)
static inline void trim(std::string &s) {
    ltrim(s);
    rtrim(s);
}
