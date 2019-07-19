/*
Filename: StubWriter.cpp
Author: David Monk
Institution: Imperial College London

Description: Add description here.
*/

#include "StubWriter.hpp"

StubWriter::StubWriter(void) {}

StubWriter::StubWriter(std::string filename) {
    openFile(filename);
}

StubWriter::~StubWriter() {
    ofs.close();
}

void StubWriter::openFile(std::string filename) {
    ofs.open(filename, std::ofstream::binary);
}