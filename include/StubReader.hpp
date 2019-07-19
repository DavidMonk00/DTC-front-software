/*
Filename: StubReader.hpp
Author: David Monk
Institution: Imperial College London

Description: Header for StubReader class.
*/

#pragma once

#include <fstream>
#include <string>
#include <vector>

#include "Stub.hpp"

class StubReader
{
private:
    std::ifstream ifs;
    std::vector<Stub> stubs;
public:
    StubReader();
    StubReader(std::string filename);
    ~StubReader(void);
    std::vector<Stub> getStubs(void);
    void openFile(std::string filename);

    using vector_type = std::vector<Stub>;
    using iterator = vector_type::iterator;
    using const_iterator = vector_type::const_iterator;

    inline iterator begin() noexcept {return stubs.begin();}
    inline const_iterator cbegin() noexcept {return stubs.cbegin();}
    inline iterator end() noexcept {return stubs.end();}
    inline const_iterator cend() noexcept {return stubs.cend();}
};
