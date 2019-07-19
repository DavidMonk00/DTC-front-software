/*
Filename: DataTypes.hpp
Author: David Monk
Institution: Imperial College London

Description: Add description here.
*/

#pragma once

#include <cstdint>

struct CICHeader {
    uint16_t boxcar_number;
    uint8_t stub_count;
};

struct CICPayload {
    bool valid;
    uint8_t bx;
    uint16_t row;
    uint8_t column;
    int8_t bend;
};

struct StubHeader {
    uint8_t bx;
    uint8_t nonant;
};

struct StubIntrinsicCoordinates {
    uint8_t strip;
    uint8_t column;
    int crossterm;
};

struct StubPayload {
    bool valid;
    int r;
    int z;
    int phi;
    int8_t alpha;
    int8_t bend;
    uint8_t layer;
    bool barrel;
    bool module;
};
