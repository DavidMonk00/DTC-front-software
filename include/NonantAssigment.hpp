/*
Filename: NonantAssigment.hpp
Author: David Monk
Institution: Imperial College London

Description: Add description here.
*/

#pragma once

#include <vector>
#include <cmath>
#include <cstdint>

#include "constants.hpp"
#include "commonfuncs.hpp"
#include "Module.hpp"

class NonantAssigment {
private:
    static constexpr float T_rphi = 612.79;
    static constexpr float B_offset = 0.493850490781;
    static constexpr float B_slope = 0.902272052533;
    static constexpr float Bfield = 3.8112;
    static constexpr float Bconv = Bfield*0.000149895;
    static constexpr float ptCut = 3;
    static constexpr float BendCut = 1.25;
    static constexpr float BconvPt = Bconv / ptCut;
    static constexpr float numPhiSecPerNon = 2;
    static constexpr float numPhiSec = 9 * numPhiSecPerNon;
    static constexpr float phiSecWidth = 2*PI/numPhiSec;
    std::vector<float> phiSec;

public:
    NonantAssigment(void);
    virtual ~NonantAssigment(void);

    int assignModule(float r, int module_type, float spacing);
    int assignModule(Module module, float phi0, uint8_t bend);

};
