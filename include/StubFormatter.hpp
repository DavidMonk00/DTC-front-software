/*
Filename: StubFormatter.hpp
Author: David Monk
Institution: Imperial College London

Description: Header for StubFormatter class.
*/

#pragma once

#include <array>
#include <string>
#include <iostream>
#include <cstdint>
#include <vector>

#include "constants.hpp"
#include "DataTypes.hpp"
#include "commonfuncs.hpp"
#include "Stub.hpp"
#include "CICStub.hpp"
#include "NonantAssigment.hpp"
#include "Correction.hpp"

class StubFormatter {
private:
    std::array<CICStub*, PAYLOAD_WIDTH> cic_array;
    std::vector<uint64_t> lut;
    int link_number;

public:
    StubFormatter(std::array<CICStub*, PAYLOAD_WIDTH> cic_arr, int link = 0);
    virtual ~StubFormatter(void);
    std::array<Stub*, PAYLOAD_WIDTH> run(std::vector<Module> modules);
};
