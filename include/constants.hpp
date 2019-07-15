#pragma once

#include <cstdint>
#include <string>

#include "Parameters.hpp"

#define PACKET_SIZE 64
#define HEADER_WIDTH 8
#define PAYLOAD_WIDTH PACKET_SIZE - HEADER_WIDTH

#define LINK_NUMBER 72

#define PI 3.14159265359

extern const std::string path;

static Parameters rParams(1200.0, 12);
static Parameters phiParams(1.02, 17);
static Parameters zParams(6000.0, 12);