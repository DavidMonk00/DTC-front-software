/*
Filename: CoordinateCorrector.hpp
Author: David Monk
Institution: Imperial College London

Description: Header for CoordinateCorrector class.
*/

#pragma once

#include <array>
#include <string>
#include <iostream>
#include <cstdint>
#include <vector>

#include "constants.hpp"
#include "commonfuncs.hpp"
#include "DataTypes.hpp"
#include "Stub.hpp"

struct Matrix
{
    int sintheta;
    int sinbeta;
    int rinv;
    int sinbeta_rsquared;
    int cosbeta;
};

class CoordinateCorrector {
private:
    std::array<Stub*, STUBS_PER_WORD*PAYLOAD_WIDTH> stubs;
    std::vector<uint64_t> lut;
    struct Matrix matrix;

public:
    CoordinateCorrector (std::array<Stub*, STUBS_PER_WORD*PAYLOAD_WIDTH> stubs_in, int link = 0);
    virtual ~CoordinateCorrector ();

    std::array<Stub*, STUBS_PER_WORD*PAYLOAD_WIDTH> run();
};
