#include "StubWriter.hpp"

StubWriter::StubWriter(void) {}

StubWriter::StubWriter(std::string filename) {
    openFile(filename);
}

StubWriter::StubWriter(std::string filename, std::vector<Stub> stubs) {
    openFile(filename);
    // writeStubs(stubs);
}

StubWriter::~StubWriter() {
    ofs.close();
}

template <template<class> class T, class Stub>
void StubWriter::writeStubs(T<Stub> stubs) {
    if (ofs.is_open()) {
        for (auto stub : stubs) {
            stub.writeRaw(ofs);
        }
    } else {
        throw std::runtime_error("Error writing stubs file: file is not open.");
    }
}

template <template<class> class T, class Stub*>
void StubWriter::writeStubs(T<Stub*> stubs) {
    if (ofs.is_open()) {
        for (auto stub : stubs) {
            stub->writeRaw(ofs);
        }
    } else {
        throw std::runtime_error("Error writing stubs file: file is not open.");
    }
}

void StubWriter::openFile(std::string filename) {
    ofs.open(filename);
}