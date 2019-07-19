/*
Filename: LinkGenerator.cpp
Author: David Monk
Institution: Imperial College London

Description: Source file defining class methods for LinkGenerator.
*/

#include "LinkGenerator.hpp"

LinkGenerator::LinkGenerator() {
    datafile.open(path + "source.txt");
    if (!datafile.is_open()) {
        throw std::runtime_error("Unable to open file");
    }
}

LinkGenerator::~LinkGenerator(void) {
    datafile.close();
}

uint64_t LinkGenerator::getLine() {
    std::string line;
    std::getline(datafile, line);
    unsigned long num = std::stoul(line, 0, 16);
    return (uint64_t)num;
}

std::array<uint64_t, PACKET_SIZE> LinkGenerator::run() {
    std::array<uint64_t, PACKET_SIZE> data_packet;
    for (int i = 0; i < PACKET_SIZE; i++) {
        data_packet[i] = getLine();
    }
    return data_packet;
}
