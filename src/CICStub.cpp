#include "CICStub.hpp"

CICStub::CICStub(void) {}

CICStub::~CICStub(void) {}

CICHeader CICStub::getHeader(void) {
	return header;
}

void CICStub::setHeader(CICHeader CICStub_header) {
	header = CICStub_header;
}

CICPayload CICStub::getPayload(void) {
	return payload;
}

void CICStub::setPayload(CICPayload CICStub_payload) {
	payload = CICStub_payload;
}
