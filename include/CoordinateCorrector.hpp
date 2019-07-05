#pragma once

#include <array>
#include <string>
#include <iostream>
#include <cstdint>
#include <vector>

#include "constants.hpp"
#include "commonfuncs.hpp"
#include "DataTypes.hpp"

class CoordinateCorrector {
private:
    std::array<Stub, PAYLOAD_WIDTH> stubs;
    std::vector<uint64_t> lut;
    std::vector<uint64_t> matrix;

public:
    CoordinateCorrector (std::array<Stub, PAYLOAD_WIDTH> stubs_in, int link = 0);
    virtual ~CoordinateCorrector ();

    std::array<Stub, PAYLOAD_WIDTH> run();
};
