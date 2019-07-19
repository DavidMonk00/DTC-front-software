/*
Filename: StubReader.cpp
Author: David Monk
Institution: Imperial College London

Description: Add description here.
*/

#include "StubReader.hpp"

StubReader::StubReader(void) {}

StubReader::StubReader(std::string filename) {
    openFile(filename);
    getStubs();
}

StubReader::~StubReader() {
    ifs.close();
}

std::vector<Stub> StubReader::getStubs(void) {
    if (ifs.is_open()) {
        Stub s;
        while (ifs.read((char*)&s, sizeof(s))) {
            stubs.push_back(s);
        }
        return stubs;
    } else {
        throw std::runtime_error("Error reading stubs file: file is not open.");
    }
}

void StubReader::openFile(std::string filename) {
    ifs.open(filename, std::ifstream::binary);
}