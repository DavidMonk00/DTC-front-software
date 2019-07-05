#pragma once

#include <string>
#include <sstream>
#include <cstring>
#include <fstream>
#include <iostream>
#include <cstdint>
#include <ios>
#include <array>

#include "constants.hpp"
#include "Entity.hpp"

class LinkGenerator : public Entity {
private:
    std::ifstream datafile;

    uint64_t getLine();

public:
    LinkGenerator (void);
    virtual ~LinkGenerator (void);
    std::array<uint64_t, PACKET_SIZE> run(void);
};
