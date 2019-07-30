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
            payload.fe_module = getSlice<uint8_t>(
                    link_in[HEADER_WIDTH + i],
                    64 - (j * STUB_WIDTH + 7), 64 - (j * STUB_WIDTH + 10));
            uint8_t strip = getSlice<uint8_t>(
                    link_in[HEADER_WIDTH + i],
                    64 - (j * STUB_WIDTH + 10), 64 - (j * STUB_WIDTH + 18));
            strip = strip << 0;
            payload.strip = (int8_t)strip;
            payload.strip = (payload.strip >> 0);
            uint8_t column = getSlice<uint8_t>(
                    link_in[HEADER_WIDTH + i],
                    64 - (j * STUB_WIDTH + 18), 64 - (j * STUB_WIDTH + 23));
            column = column << 3;
            payload.column = (int8_t)column;
            payload.column = (payload.column >> 3);
            uint8_t bend = getSlice<uint8_t>(
                    link_in[HEADER_WIDTH + i],
                    64 - (j * STUB_WIDTH + 23), 64 - (j * STUB_WIDTH + 27));
            bend = bend << 4;
            payload.bend = (int8_t)bend;
            payload.bend = (payload.bend >> 4);
            

            cic_array[STUBS_PER_WORD * i + j]->setHeader(header);
            cic_array[STUBS_PER_WORD * i + j]->setPayload(payload);
        }
    }
    return cic_array;
}
