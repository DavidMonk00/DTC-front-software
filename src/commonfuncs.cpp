#include "commonfuncs.hpp"

std::vector<uint64_t> getLUT(std::string filename) {
    std::vector<uint64_t> lut;
    std::ifstream datafile;
    std::string line;
    datafile.open(path + filename);
    if (!datafile.is_open()) {
        throw std::runtime_error("Unable to open file");
    }
    while (std::getline(datafile, line)) {
        unsigned long num = std::stoul(line, 0, 16);
        lut.push_back((uint64_t)num);
    }
    datafile.close();
    return lut;
}
