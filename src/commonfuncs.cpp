/*
Filename: commonfuncs.cpp
Author: David Monk
Institution: Imperial College London

Description: Common functions used within the codebase in multiple classes.
*/

#include "commonfuncs.hpp"

std::vector<uint64_t> getLUT(std::string filename, int lines) {
    std::vector<uint64_t> lut;
    std::ifstream datafile;
    std::string line;
    datafile.open(path + filename);
    if (!datafile.is_open()) {
        throw std::runtime_error("Unable to open file");
    }
    if (lines) {
        for (int i = 0; i < lines; i++) {
            std::getline(datafile, line);
            unsigned long num = std::stoul(line, 0, 16);
            lut.push_back((uint64_t)num);
        }
    } else {
        while (std::getline(datafile, line)) {
            unsigned long num = std::stoul(line, 0, 16);
            lut.push_back((uint64_t)num);
        }   
    }
    datafile.close();
    return lut;
}
