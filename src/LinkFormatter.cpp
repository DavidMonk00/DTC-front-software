/*
Filename: LinkFormatter.cpp
Author: David Monk
Institution: Imperial College London

Description: Source file defining class methods for LinkFormatter.
*/

#include "LinkFormatter.hpp"


LinkFormatter::LinkFormatter(std::array<uint64_t, PACKET_SIZE> packet_in) {
    link_in = packet_in;
}

LinkFormatter::~LinkFormatter(void) {}

std::array<CICStub*, STUBS_PER_WORD*PAYLOAD_WIDTH> LinkFormatter::run(void) {
    CICHeader header;
    header.boxcar_number = getSlice<uint16_t>(link_in[0], 64, 52);
    header.stub_count = getSlice<uint8_t>(link_in[0], 52, 46);

    std::array<CICStub*, STUBS_PER_WORD*PAYLOAD_WIDTH> cic_array;
    for (int i = 0; i < PAYLOAD_WIDTH; i++) {
        for (int j = 0; j < STUBS_PER_WORD; j++) {
            cic_array[STUBS_PER_WORD * i + j] = new CICStub;
            
            CICPayload payload;
            payload.valid = 1; //getSlice<bool>(link_in[HEADER_WIDTH + i], 64, 63);
            payload.bx = getSlice<uint8_t>(
                    link_in[HEADER_WIDTH + i],
                    64 - (j * STUB_WIDTH + 0), 64 - (j * STUB_WIDTH + 7));
            payload.row = getSlice<uint16_t>(
                    link_in[HEADER_WIDTH + i],
                    64 - (j * STUB_WIDTH + 7), 64 - (j * STUB_WIDTH + 18));
            payload.column = getSlice<uint8_t>(
                    link_in[HEADER_WIDTH + i],
                    64 - (j * STUB_WIDTH + 18), 64 - (j * STUB_WIDTH + 23));
            payload.bend = getSlice<int8_t>(
                    link_in[HEADER_WIDTH + i],
                    64 - (j * STUB_WIDTH + 23), 64 - (j * STUB_WIDTH + 27));

            cic_array[STUBS_PER_WORD * i + j]->setHeader(header);
            cic_array[STUBS_PER_WORD * i + j]->setPayload(payload);
        }
    }
    return cic_array;
}
