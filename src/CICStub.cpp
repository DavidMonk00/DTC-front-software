#include "CICStub.hpp"

CICStub::CICStub(void) {}

CICStub::~CICStub(void) {}

CICHeader CICStub::getHeader(void) {
	return header;
}

void CICStub::setHeader(CICHeader CICStub_header) {
	CICStub_header = header;
}

CICPayload CICStub::getPayload(void) {
	return payload;
}

void CICStub::setPayload(CICPayload CICStub_payload) {
	CICStub_payload = payload;
}

