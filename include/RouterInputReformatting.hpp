#pragma once

#include <vector>
#include <array>

#include "constants.hpp"
#include "DataTypes.hpp"
#include "commonfuncs.hpp"
#include "Stub.hpp"

class RouterInputReformatting {
private:
    std::array<Stub*, STUBS_PER_WORD*PAYLOAD_WIDTH> stubs;
public:
    RouterInputReformatting(std::array<Stub*, STUBS_PER_WORD*PAYLOAD_WIDTH> stubs);
    ~RouterInputReformatting(void);

    std::array<uint64_t, 2*STUBS_PER_WORD*PAYLOAD_WIDTH> run(void);
};
