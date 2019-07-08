#include "LinkFormatter.hpp"


LinkFormatter::LinkFormatter(std::array<uint64_t, PACKET_SIZE> packet_in) {
    link_in = packet_in;
}

LinkFormatter::~LinkFormatter(void) {}

std::array<CICStub*, PAYLOAD_WIDTH> LinkFormatter::run(void) {
    CICHeader header;
    header.boxcar_number = getSlice<uint16_t>(link_in[0], 64, 52);
    header.stub_count = getSlice<uint8_t>(link_in[0], 52, 46);

    std::array<CICStub*, PAYLOAD_WIDTH> cic_array;
    for (int i = 0; i < PAYLOAD_WIDTH; i++) {
        cic_array[i] = new CICStub;

        CICPayload payload;
        payload.valid = getSlice<bool>(link_in[HEADER_WIDTH + i], 64, 63);
        payload.bx = getSlice<uint8_t>(link_in[HEADER_WIDTH + i], 63, 57);
        payload.row = getSlice<uint16_t>(link_in[HEADER_WIDTH + i], 57, 47);
        payload.column = getSlice<uint8_t>(link_in[HEADER_WIDTH + i], 47, 43);
        payload.bend = getSlice<uint8_t>(link_in[HEADER_WIDTH + i], 43, 40);

        cic_array[i]->setHeader(header);
        cic_array[i]->setPayload(payload);
    }
    return cic_array;
}
