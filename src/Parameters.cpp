/*
Filename: Parameters.cpp
Author: David Monk
Institution: Imperial College London

Description: Source file defining class methods for Parameters.
*/

#include "Parameters.hpp"

Parameters::Parameters(float param_range, int param_bits) {
    range = param_range;
    bits = param_bits;

    basis = range/pow(2, bits);
}

Parameters::~Parameters(void) {}

float Parameters::getRange(void) {
    return range;
}

int Parameters::getBits(void) {
    return bits;
}

float Parameters::getBasis(void) {
    return basis;
}