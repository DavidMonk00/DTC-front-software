#include "StubFormatter.hpp"

StubFormatter::StubFormatter(std::array<CICStub, PAYLOAD_WIDTH> cic_arr, int link) {
    link_number = link;
    cic_array = cic_arr;
    std::array<std::vector<uint64_t>, 3> lut_file_array;
    for (int i = 0; i < 3; i++) {
        lut_file_array[i] = getLUT("random_" + std::to_string(i) + ".mif");
    }
    for (int i = 0; i < lut_file_array[0].size(); i++) {
        uint64_t word = lut_file_array[0][i] << 36;
        word += (lut_file_array[1][i] << 18);
        word += lut_file_array[2][i];
        lut.push_back(word);
    }
}

StubFormatter::~StubFormatter(void) {}

std::array<Stub, PAYLOAD_WIDTH> StubFormatter::run(void) {
    std::array<Stub, PAYLOAD_WIDTH> stub_array;
    for (int i = 0; i < PAYLOAD_WIDTH; i++) {
        int address = (link_number << 3) + (int)getSlice<uint8_t>(cic_array[i].payload.row, 11, 8);
        uint8_t bx_tmp = getSlice<uint8_t>(cic_array[i].header.boxcar_number, 5, 0) << 3;
        bx_tmp += getSlice<uint8_t>(cic_array[i].payload.bx, 3, 0);
        stub_array[i].header.bx = bx_tmp % 18;
        stub_array[i].intrinsic.strip = getSlice<uint8_t>(cic_array[i].payload.row, 8, 0);
        stub_array[i].intrinsic.column = cic_array[i].payload.column;
        stub_array[i].payload.valid = cic_array[i].payload.valid;
        stub_array[i].payload.bend = cic_array[i].payload.bend;
        stub_array[i].intrinsic.crossterm = (int)((int)getSlice<uint8_t>(cic_array[i].payload.row, 8, 0) * (int)cic_array[i].payload.column);

        stub_array[i].header.nonant = getSlice<uint8_t>(lut[address], 2, 0);
        stub_array[i].payload.r = getSlice<int>(lut[address], 14, 2);
        stub_array[i].payload.z = getSlice<int>(lut[address], 26, 14);
        stub_array[i].payload.phi = getSlice<int>(lut[address], 43, 26);
        stub_array[i].payload.alpha = getSlice<int8_t>(lut[address], 46, 43);
        stub_array[i].payload.layer = getSlice<uint8_t>(lut[address], 48, 46);
        stub_array[i].payload.barrel = getSlice<bool>(lut[address], 49, 48);
        stub_array[i].payload.module = getSlice<bool>(lut[address], 50, 49);
    }
}
