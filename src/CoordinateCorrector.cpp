#include "CoordinateCorrector.hpp"

CoordinateCorrector::CoordinateCorrector(std::array<Stub*, PAYLOAD_WIDTH> stubs_in, int link) {
    stubs = stubs_in;
    std::array<std::vector<uint64_t>, 2> lut_file_array;
    for (int i = 0; i < lut_file_array.size(); i++) {
        lut_file_array[i] = getLUT("correction_" + std::to_string(i) + ".mif", LINK_NUMBER);
    }
    for (int i = 0; i < lut_file_array[0].size(); i++) {
        uint64_t word = lut_file_array[0][i] << 36;
        word += (lut_file_array[1][i] << 18);
        word += lut_file_array[2][i];
        lut.push_back(word);
    }
    matrix.sintheta = getSlice<int>(lut[link], 6, 0);
    matrix.sinbeta = getSlice<int>(lut[link], 12, 6);
    matrix.rinv = getSlice<int>(lut[link], 18, 12);
    matrix.sinbeta_rsquared = getSlice<int>(lut[link], 24, 18);
    matrix.cosbeta = getSlice<int>(lut[link], 30, 24);
}

CoordinateCorrector::~CoordinateCorrector() {}

std::array<Stub*, PAYLOAD_WIDTH> CoordinateCorrector::run() {
    for (int i = 0; i < PAYLOAD_WIDTH; i++) {
        StubIntrinsicCoordinates intrinsic = stubs[i]->getIntrinsicCoordinates();
        StubPayload payload = stubs[i]->getPayload();
        payload.r += matrix.sinbeta*(int)intrinsic.column + matrix.sintheta*(int)intrinsic.strip;
        payload.z += matrix.cosbeta*(int)intrinsic.column;
        payload.phi += matrix.rinv*(int)intrinsic.strip + matrix.sinbeta_rsquared*(int)intrinsic.crossterm;
        stubs[i]->setPayload(payload);
    }
    return stubs;
}
