/*
Filename: CICStub.hpp
Author: David Monk
Institution: Imperial College London

Description: Header for CICStub class.
*/

#pragma once



#include "constants.hpp"
#include "DataTypes.hpp"

class CICStub {
private:


public:
    CICHeader header;
    CICPayload payload;

    CICStub(void);
    virtual ~CICStub(void);

    CICHeader getHeader(void);
    void setHeader(CICHeader header);
    CICPayload getPayload(void);
    void setPayload(CICPayload payload);
};
