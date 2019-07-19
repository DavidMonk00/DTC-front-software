/*
Filename: Stub.hpp
Author: David Monk
Institution: Imperial College London

Description: Header for Stub class.
*/

#pragma once

#include <iostream>
#include <ios>
#include <fstream>

#include "constants.hpp"
#include "DataTypes.hpp"


class Stub {
private:
    StubHeader header;
    StubIntrinsicCoordinates intrinsic;
    StubPayload payload;

public:
    Stub(void);
    ~Stub(void);

    StubHeader getHeader(void);
    StubIntrinsicCoordinates getIntrinsicCoordinates(void);
    StubPayload getPayload(void);

    void setHeader(StubHeader header);
    void setIntrinsicCoordinates(StubIntrinsicCoordinates intrinsic);
    void setPayload(StubPayload payload);

    void print(void);
    void writeRaw(std::ofstream& file);
};
