/*
Filename: CoordinateCorrector.cpp
Author: David Monk
Institution: Imperial College London

Description: Source file defining class methods for CoordinateCorrector.
*/

#include "CoordinateCorrector.hpp"

CoordinateCorrector::CoordinateCorrector(std::array<Stub*, STUBS_PER_WORD*PAYLOAD_WIDTH> stubs_in, int link) {
    stubs = stubs_in;
    std::array<std::vector<uint64_t>, 2> lut_file_array; 
    for (int i = 0; i < lut_file_array.size(); i++) {
        lut_file_array[i] = getLUT("correction_" + std::to_string(i) + ".mif", LINK_NUMBER*FE_MODULES);
    }
    for (int i = 0; i < lut_file_array[0].size(); i++) {
        uint64_t word = lut_file_array[0][i] << 0;
        word += (lut_file_array[1][i] << 18);
        lut.push_back(word);
    }
    for (int i = 0; i < STUBS_PER_WORD*PAYLOAD_WIDTH; i++) {
        int address = (link << 3) + stubs[i]->getIntrinsicCoordinates().fe_module;
        matrices[i].sintheta = getSlice<uint8_t, int8_t>(lut[address], 6, 0);
        matrices[i].sinbeta = getSlice<uint8_t, int8_t>(lut[address], 12, 6);
        matrices[i].rinv = getSlice<uint8_t, int8_t>(lut[address], 18, 12);
        matrices[i].sinbeta_rsquared = getSlice<uint8_t, int8_t>(lut[address], 24, 18);
        matrices[i].cosbeta = getSlice<uint8_t, int8_t>(lut[address], 30, 24);
    }
    
}

CoordinateCorrector::~CoordinateCorrector() {}

std::array<Stub*, STUBS_PER_WORD*PAYLOAD_WIDTH> CoordinateCorrector::run() {
    for (int i = 0; i < STUBS_PER_WORD*PAYLOAD_WIDTH; i++) {
        StubIntrinsicCoordinates intrinsic = stubs[i]->getIntrinsicCoordinates();
        StubPayload payload = stubs[i]->getPayload();
        payload.r += matrices[i].sinbeta*(int)intrinsic.column + matrices[i].sintheta*(int)intrinsic.strip;
        payload.z += matrices[i].cosbeta*(int)intrinsic.column;
        payload.phi += matrices[i].rinv*(int)intrinsic.strip + matrices[i].sinbeta_rsquared*(int)intrinsic.crossterm;
        stubs[i]->setPayload(payload);
    }
    return stubs;
}
