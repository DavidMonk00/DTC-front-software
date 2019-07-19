/*
Filename: Parameters.hpp
Author: David Monk
Institution: Imperial College London

Description: Header for Parameters class.
*/

#pragma once

#include <cmath>

class Parameters
{
private:
    float range;
    int bits;
    float basis;

public:
    Parameters(float param_range, int param_bits);
    ~Parameters(void);

    float getRange(void);
    int getBits(void);
    float getBasis(void);
};
