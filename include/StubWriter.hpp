/*
Filename: StubWriter.hpp
Author: David Monk
Institution: Imperial College London

Description: Header for StubWriter class.
*/

#pragma once

#include <fstream>
#include <string>
#include <vector>

#include "Stub.hpp"

class StubWriter
{
private:
    std::ofstream ofs;
    std::vector<Stub> stubs;
public:
    StubWriter();
    StubWriter(std::string filename);
    template <class T>
    StubWriter(std::string filename, T stubs);
    ~StubWriter(void);

    template <class T>
    void writeStubs(T stubs);
    void openFile(std::string filename);
};

template <class T>
StubWriter::StubWriter(std::string filename, T stubs) {
    openFile(filename);
    writeStubs(stubs);
}

template <class T>
void StubWriter::writeStubs(T stubs) {
    if (ofs.is_open()) {
        for (auto stub : stubs) {
            stub->writeRaw(ofs);
        }
    } else {
        throw std::runtime_error("Error writing stubs file: file is not open.");
    }
}