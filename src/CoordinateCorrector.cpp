#include "CoordinateCorrector.hpp"

CoordinateCorrector::CoordinateCorrector(std::array<Stub*, PAYLOAD_WIDTH> stubs_in, int link) {
    stubs = stubs_in;
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
    matrix.sintheta = getSlice<int>(lut[link], 5, 0);
    matrix.sinbeta = getSlice<int>(lut[link], 10, 5);
    matrix.rinv = getSlice<int>(lut[link], 15, 10);
    matrix.sinbeta_rsquared = getSlice<int>(lut[link], 20, 15);
    matrix.cosbeta = getSlice<int>(lut[link], 25, 20);
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
