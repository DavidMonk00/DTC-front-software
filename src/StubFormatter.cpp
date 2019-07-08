#include "StubFormatter.hpp"

StubFormatter::StubFormatter(std::array<CICStub*, PAYLOAD_WIDTH> cic_arr, int link) {
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

std::array<Stub*, PAYLOAD_WIDTH> StubFormatter::run(void) {
    std::array<Stub*, PAYLOAD_WIDTH> stub_array;
    for (int i = 0; i < PAYLOAD_WIDTH; i++) {
        CICHeader cic_header = cic_array[i]->getHeader();
        CICPayload cic_payload = cic_array[i]->getPayload();

        stub_array[i] = new Stub;
        int address = (link_number << 3) + (int)getSlice<uint8_t>(cic_payload.row, 11, 8);
        uint8_t bx_tmp = getSlice<uint8_t>(cic_header.boxcar_number, 5, 0) << 3;
        bx_tmp += getSlice<uint8_t>(cic_payload.bx, 3, 0);

        StubHeader header;
        StubIntrinsicCoordinates intrinsic;
        StubPayload payload;

        header.bx = bx_tmp % 18;
        intrinsic.strip = getSlice<uint8_t>(cic_payload.row, 8, 0);
        intrinsic.column = cic_payload.column;
        payload.valid = cic_payload.valid;
        payload.bend = cic_payload.bend;
        intrinsic.crossterm = (int)((int)getSlice<uint8_t>(cic_payload.row, 8, 0) * (int)cic_payload.column);

        header.nonant = getSlice<uint8_t>(lut[address], 2, 0);
        payload.r = getSlice<int>(lut[address], 14, 2);
        payload.z = getSlice<int>(lut[address], 26, 14);
        payload.phi = getSlice<int>(lut[address], 43, 26);
        payload.alpha = getSlice<int8_t>(lut[address], 46, 43);
        payload.layer = getSlice<uint8_t>(lut[address], 48, 46);
        payload.barrel = getSlice<bool>(lut[address], 49, 48);
        payload.module = getSlice<bool>(lut[address], 50, 49);

        stub_array[i]->setHeader(header);
        stub_array[i]->setIntrinsicCoordinates(intrinsic);
        stub_array[i]->setPayload(payload);
    }
    return stub_array;
}
