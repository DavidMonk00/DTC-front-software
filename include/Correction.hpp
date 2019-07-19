/*
Filename: Correction.hpp
Author: David Monk
Institution: Imperial College London

Description: Add description here.
*/

#pragma once

#include <cmath>

#include "constants.hpp"
#include "Module.hpp"

class Correction {
protected:
    Module* module;
    float cosbeta;
    float sinbeta;
public:
    Correction(Module* arg_module);
    ~Correction(void);

    float getCosBeta(void);
    float getSinBeta(void);

    virtual float r(float x, float z)=0;
    virtual float phi(float x, float z)=0;
    virtual float z(float x, float z)=0;
};


class ExactCorrection : public Correction {
public:
    using Correction::Correction;

    float r(float x, float z);
    float phi(float x, float z);
    float z(float x, float z);
};

// class ExactCorrection : public Correction {
// public:
//     float r(float x, float z);
//     float phi(float x, float z);
//     float z(float x, float z);
// };