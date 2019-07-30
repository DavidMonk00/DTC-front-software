#include "RouterInputReformatting.hpp"

RouterInputReformatting::RouterInputReformatting(std::array<Stub*, STUBS_PER_WORD*PAYLOAD_WIDTH> stubs) {
    this->stubs = stubs;
}

RouterInputReformatting::~RouterInputReformatting(void) {}

std::array<uint64_t, 2*STUBS_PER_WORD*PAYLOAD_WIDTH> RouterInputReformatting::run(void) {
    std::array<uint64_t, 2*STUBS_PER_WORD*PAYLOAD_WIDTH> words_out;
    for (int i = 0; i < STUBS_PER_WORD*PAYLOAD_WIDTH; i++) {
        words_out[2 * i] = 0;
        words_out[2 * i] = setSlice<uint8_t>(words_out[2 * i], (uint8_t)stubs[i]->getHeader().bx, 0);
        words_out[2 * i] |= setSlice<uint8_t>(words_out[2 * i], (uint8_t)stubs[i]->getHeader().nonant, 5);
        words_out[2 * i + 1] = 0;
        words_out[2 * i + 1] = setSlice<uint8_t>(words_out[2 * i + 1], (uint8_t)stubs[i]->getPayload().valid, 0);
        words_out[2 * i + 1] |= setSlice<uint16_t>(words_out[2 * i + 1], (uint16_t)stubs[i]->getPayload().r, 1);
        words_out[2 * i + 1] |= setSlice<int16_t>(words_out[2 * i + 1], (int16_t)stubs[i]->getPayload().z, 13);
        words_out[2 * i + 1] |= setSlice<int32_t>(words_out[2 * i + 1], (int32_t)stubs[i]->getPayload().phi, 25);
        words_out[2 * i + 1] |= setSlice<uint8_t>(words_out[2 * i + 1], (uint8_t)stubs[i]->getPayload().alpha, 42);
        words_out[2 * i + 1] |= setSlice<uint8_t>(words_out[2 * i + 1], (uint8_t)stubs[i]->getPayload().bend, 46);
        words_out[2 * i + 1] |= setSlice<uint8_t>(words_out[2 * i + 1], (uint8_t)stubs[i]->getPayload().layer, 50);
        words_out[2 * i + 1] |= setSlice<uint8_t>(words_out[2 * i + 1], (uint8_t)stubs[i]->getPayload().barrel, 52);
        words_out[2 * i + 1] |= setSlice<uint8_t>(words_out[2 * i + 1], (uint8_t)stubs[i]->getPayload().module, 53);
    }
    return words_out;
}