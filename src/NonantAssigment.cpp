#include "NonantAssigment.hpp"

NonantAssigment::NonantAssigment(void) {
    for (int i = 0; i < numPhiSecPerNon; i++) {
        phiSec.push_back((1 + 2*i - numPhiSecPerNon) * (phiSecWidth/2));
    }


}

NonantAssigment::~NonantAssigment(void) {

}

// int NonantAssigment::assignModule(float r, int module_type, float spacing) {
//     float rT = r - T_rphi;
//     float A = (module_type) ? 0.089/spacing : 0.099/spacing;
//     float B;
//     float tilt = module.getTilt_angle();
//     if (tilt == 0) {
//         B = 1
//     } else if (tilt == 90) {
//         B = abs(module.getZ()) * 1/r
//     }
//     float C = rT*(1/r);
//     float D = A*B;
//     return D > 0;
// }

int NonantAssigment::assignModule(Module module) {
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
    std::cout << A << " " << B << '\n';

    float C = rT*(1/r);
    float D = A*B;
    std::cout << C << " " << D << '\n';

    float phiRes = abs(rT) * BconvPt;
    float estPhiRes = BendCut * D * fabs(C);
    std::cout << estPhiRes << '\n';
    estPhiRes = (estPhiRes < phiSecWidth/2) ? estPhiRes : phiSecWidth/2;
    std::cout << phiRes << " " << estPhiRes << '\n';
    std::cout << std::endl;
    // float deltaPhi = phi0 - phiSec[0];
    // float deltaEstPhi = deltaPhi + bend * D * C;
    // return D > 0;
}
