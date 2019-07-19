/*
Filename: CICStub.cpp
Author: David Monk
Institution: Imperial College London

Description: Source file defining class methods for CICStub.
*/

#include "CICStub.hpp"

CICStub::CICStub(void) {}

CICStub::~CICStub(void) {}

CICHeader CICStub::getHeader(void) {
	return header;
}

void CICStub::setHeader(CICHeader header) {
	this->header = header;
}

CICPayload CICStub::getPayload(void) {
	return payload;
}

void CICStub::setPayload(CICPayload payload) {
	this->payload = payload;
}
