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
    StubWriter(std::string filename, std::vector<Stub> stubs);
    ~StubWriter(void);

    template <class T>
    void writeStubs(T stubs);
    void openFile(std::string filename);
};