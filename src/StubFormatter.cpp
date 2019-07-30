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
        lut_file_array[i] = getLUT("modules_" + std::to_string(i) + ".mif", LINK_NUMBER);
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
        
        int fe_module = (int)getSlice<uint8_t>(cic_payload.row, 10, 7);
        int address = (link_number << 3) + fe_module;


        uint8_t bx_tmp = getSlice<uint8_t>(cic_header.boxcar_number, 5, 0) << 3;
        bx_tmp += getSlice<uint8_t>(cic_payload.bx, 3, 0);

        StubHeader header;
        StubIntrinsicCoordinates intrinsic;
        StubPayload payload;

        header.bx = bx_tmp % 18;
        intrinsic.strip = getSlice<uint8_t>(cic_payload.row, 7, 0);
        intrinsic.column = cic_payload.column;
        payload.valid = cic_payload.valid;
        payload.bend = cic_payload.bend;
        intrinsic.crossterm = (int)((int)getSlice<uint8_t>(cic_payload.row, 8, 0) * (int)cic_payload.column);

        payload.r = getSlice<int>(lut[address], 12, 0);
        payload.z = getSlice<int>(lut[address], 24, 12);
        payload.phi = getSlice<int>(lut[address], 41, 24);
        payload.alpha = getSlice<int8_t>(lut[address], 44, 41);
        payload.layer = getSlice<uint8_t>(lut[address], 46, 44);
        payload.barrel = getSlice<bool>(lut[address], 47, 46);
        payload.module = getSlice<bool>(lut[address], 48, 47);


        float phi0 =  (float)cic_payload.row * phiParams.getBasis();
        float bend = 2.5 * (float)cic_payload.bend/pow(2,3) - 1.25;
        header.nonant = (uint8_t)assigner.assignModule(modules[i], phi0, bend);

        stub_array[i]->setHeader(header);
        stub_array[i]->setIntrinsicCoordinates(intrinsic);
        stub_array[i]->setPayload(payload);
    }
    return stub_array;
}
