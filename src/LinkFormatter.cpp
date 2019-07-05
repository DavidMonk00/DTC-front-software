#include "LinkFormatter.hpp"


LinkFormatter::LinkFormatter(std::array<uint64_t, PACKET_SIZE> packet_in) {
    link_in = packet_in;
}

LinkFormatter::~LinkFormatter(void) {}

std::array<CICStub, PAYLOAD_WIDTH> LinkFormatter::run(void) {
    CICHeader cic_header;
    cic_header.boxcar_number = getSlice<uint16_t>(link_in[0], 64, 52);
    cic_header.stub_count = getSlice<uint8_t>(link_in[0], 52, 46);
    std::array<CICStub, PAYLOAD_WIDTH> cic_array;
    for (int i = 0; i < PAYLOAD_WIDTH; i++) {
        cic_array[i].header = cic_header;
        cic_array[i].payload.valid = getSlice<bool>(link_in[HEADER_WIDTH + i], 64, 63);
        cic_array[i].payload.bx = getSlice<uint8_t>(link_in[HEADER_WIDTH + i], 63, 57);
        cic_array[i].payload.row = getSlice<uint16_t>(link_in[HEADER_WIDTH + i], 57, 47);
        cic_array[i].payload.column = getSlice<uint8_t>(link_in[HEADER_WIDTH + i], 47, 43);
        cic_array[i].payload.bend = getSlice<uint8_t>(link_in[HEADER_WIDTH + i], 43, 40);
    }
    return cic_array;
}
