#include "CoordinateCorrector.hpp"

CoordinateCorrector::CoordinateCorrector(std::array<Stub, PAYLOAD_WIDTH> stubs_in, int link) {
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
    for (int i = 0; i < 6; i++) {
        matrix.push_back(getSlice<int>(lut[link], 5, 0));
    }
}

CoordinateCorrector::~CoordinateCorrector() {}

std::array<Stub, PAYLOAD_WIDTH> CoordinateCorrector::run() {
    for (int i = 0; i < PAYLOAD_WIDTH; i++) {
        stubs[i].payload.r += (matrix[0]*(int)stubs[i].intrinsic.strip + matrix[1]*(int)stubs[i].intrinsic.column);
        stubs[i].payload.z += (matrix[2]*(int)stubs[i].intrinsic.strip + matrix[3]*(int)stubs[i].intrinsic.column);
        stubs[i].payload.phi += (matrix[4]*(int)stubs[i].intrinsic.strip + matrix[5]*(int)stubs[i].intrinsic.column);
    }
    return stubs;
}
