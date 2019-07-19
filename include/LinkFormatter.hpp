/*
Filename: LinkFormatter.hpp
Author: David Monk
Institution: Imperial College London

Description: Header for LinkFormatter class.
*/

#include <vector>
#include <array>
#include <cstdint>
#include <iostream>

#include "constants.hpp"
#include "DataTypes.hpp"
#include "Entity.hpp"
#include "commonfuncs.hpp"
#include "CICStub.hpp"

class LinkFormatter : public Entity {
private:
    std::array<uint64_t, PACKET_SIZE> link_in;

public:
    LinkFormatter (std::array<uint64_t, PACKET_SIZE> packet_in);
    virtual ~LinkFormatter (void);

    std::array<CICStub*, PAYLOAD_WIDTH> run(void);
};
