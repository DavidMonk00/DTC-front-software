#pragma once

#include <cstdint>
#include <string>

#include "Parameters.hpp"

#define PACKET_SIZE 64
#define HEADER_WIDTH 8
#define PAYLOAD_WIDTH PACKET_SIZE - HEADER_WIDTH

#define LINK_NUMBER 36

#define PI 3.14159265359

extern const std::string path;

// namespace dtc {
    
// } // namespace dtc

static Parameters rParams(75.0, 7);
static Parameters phiParams(1.02607, 14);
static Parameters zParams(240.0, 12);