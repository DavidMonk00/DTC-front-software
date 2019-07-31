/*
Filename: DataTypes.hpp
Author: David Monk
Institution: Imperial College London

Description: Header file defining stub data formats.
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
    uint8_t fe_module;
    int8_t strip;
    int8_t column;
    int8_t bend;
};

struct StubHeader {
    uint8_t bx;
    uint8_t nonant;
};

struct StubIntrinsicCoordinates {
    int8_t strip;
    int8_t column;
    int crossterm;
    uint8_t fe_module;
};

struct StubPayload {
    bool valid;
    uint16_t r;
    int16_t z;
    int32_t phi;
    int8_t alpha;
    int8_t bend;
    uint8_t layer;
    bool barrel;
    bool module;
};
