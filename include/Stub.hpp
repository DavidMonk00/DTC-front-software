#pragma once

#include <iostream>
#include <ios>

#include "constants.hpp"
#include "DataTypes.hpp"


class Stub {
private:
    StubHeader header;
    StubIntrinsicCoordinates intrinsic;
    StubPayload payload;

public:
    Stub(void);
    virtual ~Stub(void);

    StubHeader getHeader(void);
    StubIntrinsicCoordinates getIntrinsicCoordinates(void);
    StubPayload getPayload(void);

    void setHeader(StubHeader stub_header);
    void setIntrinsicCoordinates(StubIntrinsicCoordinates stub_intrinsic);
    void setPayload(StubPayload stub_payload);

    void print(void);
};
