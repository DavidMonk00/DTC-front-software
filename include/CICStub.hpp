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
    void setHeader(CICHeader CICStub_header);
    CICPayload getPayload(void);
    void setPayload(CICPayload CICStub_payload);
};
