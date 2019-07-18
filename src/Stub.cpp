#include "Stub.hpp"

Stub::Stub(void) {}

Stub::~Stub(void) {}

StubHeader Stub::getHeader(void) {
    return header;
}

StubIntrinsicCoordinates Stub::getIntrinsicCoordinates(void) {
    return intrinsic;
}

StubPayload Stub::getPayload(void) {
    return payload;
}

void Stub::setHeader(StubHeader header) {
    this->header = header;
}

void Stub::setIntrinsicCoordinates(StubIntrinsicCoordinates intrinsic) {
    this->intrinsic = intrinsic;
}

void Stub::setPayload(StubPayload payload) {
    this->payload = payload;
}

void Stub::print(void) {
    std::cout << "----- Header -----" << '\n';
    std::cout << "bx: " << std::dec << (int)header.bx << '\n';
    std::cout << "nonant: " << std::dec << (int)header.nonant << '\n';
    std::cout << "----- Intrinsic Coordinates -----" << '\n';
    std::cout << "strip: " << std::dec << (int)intrinsic.strip << '\n';
    std::cout << "column: " << std::dec << (int)intrinsic.column << '\n';
    std::cout << "crossterm: " << std::dec << (int)intrinsic.crossterm << '\n';
    std::cout << "----- Payload -----" << '\n';
    std::cout << "valid: " << std::boolalpha << payload.valid << '\n';
    std::cout << "r: " << std::dec << (int)payload.r << '\n';
    std::cout << "z: " << std::dec << (int)payload.z << '\n';
    std::cout << "phi: " << std::dec << (int)payload.phi << '\n';
    std::cout << "alpha: " << std::dec << (int)payload.alpha << '\n';
    std::cout << "bend: " << std::dec << (int)payload.bend << '\n';
    std::cout << "layer: " << std::dec << (int)payload.layer << '\n';
    std::cout << "barrel: " << std::boolalpha << payload.barrel << '\n';
    std::cout << "module: " << std::boolalpha << payload.module << "\n\n";
}

void Stub::writeRaw(std::ofstream& file) {
    file.write((char*)this, sizeof(*this));
}
