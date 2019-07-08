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
    for (int i = 0; i < 4; i++) {
        matrix.push_back(getSlice<int>(lut[link], 5, 0));
    }
}

CoordinateCorrector::~CoordinateCorrector() {}

std::array<Stub*, PAYLOAD_WIDTH> CoordinateCorrector::run() {
    for (int i = 0; i < PAYLOAD_WIDTH; i++) {
        StubIntrinsicCoordinates intrinsic = stubs[i]->getIntrinsicCoordinates();
        StubPayload payload = stubs[i]->getPayload();
        payload.r += matrix[0]*(int)intrinsic.column;
        payload.z += matrix[1]*(int)intrinsic.column;
        payload.phi += (matrix[2]*(int)intrinsic.strip + matrix[3]*(int)intrinsic.crossterm);
        #ifdef DEBUG
        stubs[i]->print();
        #endif
    }
    return stubs;
}
