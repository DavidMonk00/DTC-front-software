/*
Filename: StubFormatter.cpp
Author: David Monk
Institution: Imperial College London

Description: Source file defining class methods for StubFormatter.
*/

#include "StubFormatter.hpp"

StubFormatter::StubFormatter(std::array<CICStub*, STUBS_PER_WORD*PAYLOAD_WIDTH> cic_arr, int link) {
    link_number = link;
    cic_array = cic_arr;
    std::array<std::vector<uint64_t>, 3> lut_file_array;
    for (int i = 0; i < 3; i++) {
        lut_file_array[i] = getLUT("modules_" + std::to_string(i) + ".mif", STUBS_PER_WORD*LINK_NUMBER*FE_MODULES);
    }
    for (int i = 0; i < lut_file_array[0].size(); i++) {
        uint64_t word = lut_file_array[2][i] << 36;
        word += (lut_file_array[1][i] << 18);
        word += lut_file_array[0][i];
        lut.push_back(word);
    }
}

StubFormatter::~StubFormatter(void) {}

std::array<Stub*, STUBS_PER_WORD*PAYLOAD_WIDTH> StubFormatter::run(std::vector<Module> modules) {
    NonantAssigment assigner;

    std::array<Stub*, STUBS_PER_WORD*PAYLOAD_WIDTH> stub_array;
    for (int i = 0; i < STUBS_PER_WORD*PAYLOAD_WIDTH; i++) {
        CICHeader cic_header = cic_array[i]->getHeader();
        CICPayload cic_payload = cic_array[i]->getPayload();

        stub_array[i] = new Stub;
        
        int address = ((STUBS_PER_WORD*link_number + i % STUBS_PER_WORD) << 3) + cic_payload.fe_module;

        uint8_t bx_tmp = getSlice<uint8_t, uint8_t>(cic_header.boxcar_number, 5, 0) << 3;
        bx_tmp += getSlice<uint8_t, uint8_t>(cic_payload.bx, 3, 0);

        StubHeader header;
        StubIntrinsicCoordinates intrinsic;
        StubPayload payload;

        header.bx = bx_tmp % 18;
        intrinsic.strip = cic_payload.strip;
        intrinsic.column = cic_payload.column;
        intrinsic.fe_module = cic_payload.fe_module;
        payload.valid = cic_payload.valid;
        payload.bend = cic_payload.bend;
        intrinsic.crossterm = (int)cic_payload.strip * (int)cic_payload.column;

        payload.r = getSlice<uint16_t, uint16_t>(lut[address], 12, 0);
        payload.z = getSlice<uint16_t, int16_t>(lut[address], 24, 12);
        payload.phi = getSlice<uint32_t, int32_t>(lut[address], 41, 24);
        payload.alpha = getSlice<uint8_t, int8_t>(lut[address], 45, 41);
        payload.layer = getSlice<uint8_t, uint8_t>(lut[address], 46, 45);
        payload.barrel = getSlice<bool, bool>(lut[address], 47, 46);
        payload.module = getSlice<bool, bool>(lut[address], 48, 47);


        float phi0 =  (float)cic_payload.strip * phiParams.getBasis(); //THIS IS NOT CORRECT - phi0 needs to be provided after after phi has been looked up - (befor coorrection ok?)
        float bend = 2.5 * (float)cic_payload.bend/pow(2,3) - 1.25;
        header.nonant = (uint8_t)assigner.assignModule(modules[i], phi0, bend);

        stub_array[i]->setHeader(header);
        stub_array[i]->setIntrinsicCoordinates(intrinsic);
        stub_array[i]->setPayload(payload);
    }
    return stub_array;
}
