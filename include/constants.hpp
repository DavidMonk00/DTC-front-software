/*
Filename: constants.hpp
Author: David Monk
Institution: Imperial College London

Description: Header file for constants used in the codebase.
*/

#pragma once

#include <cstdint>
#include <string>

#include "Parameters.hpp"

static const int PACKET_SIZE = 64;
static const int HEADER_WIDTH = 6;
static const int PAYLOAD_WIDTH = (PACKET_SIZE - HEADER_WIDTH);
static const int STUB_WIDTH = 32;

static const int LINK_NUMBER = 18;
static const int STUBS_PER_WORD = 1;

static const int FE_MODULES = 8;

static constexpr float PI = 3.14159265359;

extern const std::string path;

static Parameters rParams(1200.0, 12);
static Parameters phiParams(1.02607, 17);
static Parameters zParams(2400.0, 12);