/*
Filename: Correction.cpp
Author: David Monk
Institution: Imperial College London

Description: Source file defining class methods for Correction.
*/

#include "Correction.hpp"

float degToRad(float deg) {
    return PI*deg/180;
}

Correction::Correction(Module* arg_module) {
    module = arg_module;
    cosbeta = cos(degToRad(module->getTilt_angle()));
    cosbeta = sin(degToRad(module->getTilt_angle()));
}

Correction::~Correction() {
}

float Correction::getCosBeta(void) {
    return cosbeta;
}

float Correction::getSinBeta(void) {
    return sinbeta;
}

float ExactCorrection::r(float x, float z) {
    float r0 = module->getR() + z * sinbeta;
    return sqrt(x * x + r0 * r0);
}

float ExactCorrection::phi(float x, float z) {
    float r0 = module->getR() + z * sinbeta;
    return atan(x / r0);
}

float ExactCorrection::z(float x, float z) {
    return module->getZ() + z * cosbeta;
}