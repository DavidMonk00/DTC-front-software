#pragma once

#include <vector>
#include <array>

#include "constants.hpp"
#include "DataTypes.hpp"
#include "commonfuncs.hpp"
#include "Stub.hpp"

class RouterInputReformatting {
private:
    std::array<Stub*, PAYLOAD_WIDTH> stubs;
public:
    RouterInputReformatting(std::array<Stub*, PAYLOAD_WIDTH> stubs);
    ~RouterInputReformatting(void);

    std::array<uint64_t, 2*PAYLOAD_WIDTH> run(void);
};
