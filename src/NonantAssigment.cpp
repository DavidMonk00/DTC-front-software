/*
Filename: NonantAssigment.cpp
Author: David Monk
Institution: Imperial College London

Description: Source file defining class methods for NonantAssignment.
*/

#include "NonantAssigment.hpp"

NonantAssigment::NonantAssigment(void) {
    for (int i = 0; i < numPhiSecPerNon; i++) {
        phiSec.push_back((1 + 2*i - numPhiSecPerNon) * (phiSecWidth/2));
    }
}

NonantAssigment::~NonantAssigment(void) {

}

int NonantAssigment::assignModule(Module module, float phi0, uint8_t bend) {
    float r = module.getR();
    float z = module.getZ();
    float rT = r - T_rphi;
    float A = (module.getModule_type()) ? 0.089/module.getSpacing() : 0.099/module.getSpacing();
    float B;
    float tilt = module.getTilt_angle();
    if (tilt == 0) {
        B = 1;
    } else if (tilt == 90) {
        B = fabs(z) * 1/r;
    } else {
        B = B_offset + B_slope * (fabs(z)/r);
    }

    float C = rT*(1/r);
    float D = A*B;

    float phiRes = abs(rT) * BconvPt;
    float estPhiRes = BendCut * D * fabs(C);
    estPhiRes = (estPhiRes < phiSecWidth/2) ? estPhiRes : phiSecWidth/2;
    int sectors = 0;
    for (int i = 0; i < phiSec.size(); i++) {
        float deltaPhi = phi0 - phiSec[i];
        float deltaEstPhi = deltaPhi + (float)(int)bend * D * C;
        
        bool deltaPhiChk = fabs(deltaPhi) < phiSecWidth/2 + phiRes;
        bool deltaEstPhiChk = fabs(deltaEstPhi) < phiSecWidth/2 + estPhiRes;
        if (deltaPhiChk && deltaEstPhiChk) {
            sectors += i + 1;
        }
    }
    return sectors;
}
