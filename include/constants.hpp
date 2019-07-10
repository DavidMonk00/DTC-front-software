#include <cstdint>
#include <string>

#define PACKET_SIZE 64
#define HEADER_WIDTH 8
#define PAYLOAD_WIDTH PACKET_SIZE - HEADER_WIDTH

#define LINK_NUMBER 36

#define PI 3.14159265359

extern const std::string path;

const struct {
    /* unit: mm */
    float range;
    int bits;
} rParameters = {75.0, 7};

const struct {
    /* unit: rad */
    float range;
    int bits;
} phiParameters  = {1.02607, 14};

const struct {
    /* unit: mm */
    float range;
    int bits;
} zParameters = {240.0, 12};