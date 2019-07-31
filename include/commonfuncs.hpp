/*
Filename: commonfuncs.hpp
Author: David Monk
Institution: Imperial College London

Description: Header file for commmon fucntions used within the codebase.
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

template <class S, class T>
T getSlice(uint64_t word, int start, int end) {
    int bit_length = start - end;
    uint64_t slice = word << (64 - start);
    S unsigned_type = (S)(slice >> (64 - bit_length));
    unsigned_type = unsigned_type << (sizeof(T)*__CHAR_BIT__ - bit_length);
    return ((T)unsigned_type) >> (sizeof(T)*__CHAR_BIT__ - bit_length);
}

template <class T>
uint64_t setSlice(uint64_t word, T slice, int high, int low) {
    int64_t ss = (int64_t)slice;
    ss = ss << (64 - (high - low));
    uint64_t s = (uint64_t)ss;
    s = s >> (64 - high);
    return word | s;
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
