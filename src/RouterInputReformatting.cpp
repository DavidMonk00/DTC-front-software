#include "RouterInputReformatting.hpp"

RouterInputReformatting::RouterInputReformatting(std::array<Stub*, STUBS_PER_WORD*PAYLOAD_WIDTH> stubs) {
    this->stubs = stubs;
}

RouterInputReformatting::~RouterInputReformatting(void) {}

std::array<uint64_t, 2*STUBS_PER_WORD*PAYLOAD_WIDTH> RouterInputReformatting::run(void) {
    std::array<uint64_t, 2*STUBS_PER_WORD*PAYLOAD_WIDTH> words_out;
    for (int i = 0; i < STUBS_PER_WORD*PAYLOAD_WIDTH; i++) {
        // stubs[i]->print();
        words_out[2 * i] = 0;
        words_out[2 * i] = setSlice<uint8_t>(words_out[2 * i], (uint8_t)stubs[i]->getHeader().bx, 5, 0);
        // words_out[2 * i] |= setSlice<uint8_t>(words_out[2 * i], (uint8_t)stubs[i]->getHeader().nonant, 7, 5);
        words_out[2 * i + 1] = 0;
        words_out[2 * i + 1] |= setSlice<uint16_t>(words_out[2 * i + 1], (uint16_t)stubs[i]->getPayload().r, 12, 0);
        words_out[2 * i + 1] |= setSlice<int16_t>(words_out[2 * i + 1], (int16_t)stubs[i]->getPayload().z, 24, 12);
        words_out[2 * i + 1] |= setSlice<int32_t>(words_out[2 * i + 1], (int32_t)stubs[i]->getPayload().phi, 41, 24);
        words_out[2 * i + 1] |= setSlice<uint8_t>(words_out[2 * i + 1], (uint8_t)stubs[i]->getPayload().alpha, 45, 41);
        words_out[2 * i + 1] |= setSlice<uint8_t>(words_out[2 * i + 1], (uint8_t)stubs[i]->getPayload().bend, 49, 45);
        words_out[2 * i + 1] |= setSlice<uint8_t>(words_out[2 * i + 1], (uint8_t)stubs[i]->getPayload().layer, 51, 49);
        words_out[2 * i + 1] |= setSlice<uint8_t>(words_out[2 * i + 1], (uint8_t)stubs[i]->getPayload().barrel, 51, 51);
        words_out[2 * i + 1] |= setSlice<uint8_t>(words_out[2 * i + 1], (uint8_t)stubs[i]->getPayload().module, 52, 52);
    }
    return words_out;
}