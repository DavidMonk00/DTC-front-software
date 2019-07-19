/*
Filename: Geometry.cpp
Author: David Monk
Institution: Imperial College London

Description: Source file defining class methods for Geometry.
*/

#include "Geometry.hpp"

template <class T>
T setBit(T bits, int n) {
    return bits |= 1UL << n;
}

Geometry::Geometry(void) {
    datafile.open(path + "allCoordinates.csv");
    if (!datafile.is_open()) {
        throw std::runtime_error("Unable to open file");
    }
}

Geometry::~Geometry(void) {}

std::vector<std::string> Geometry::splitLine(std::string line) {
    std::vector<std::string> result;
    std::stringstream lineStream(line);
    std::string cell;
    while(std::getline(lineStream,cell, ',')) {
        result.push_back(cell);
    }
    return result;
}

std::vector<Module> Geometry::getData(void) {
    std::string line;
    std::getline(datafile, line);
    while(std::getline(datafile, line)) {
        modules.push_back(Module(splitLine(line)));
    }
    return modules;
}

std::vector<Module> Geometry::getModules(void) {
    return modules;
}

void Geometry::setModules(std::vector<Module> modules) {
    this->modules = modules;
}

void Geometry::runNonantAssignment(void) {
    NonantAssigment assigner;
    for (auto i : modules) {
        std::cout << assigner.assignModule(i, 0.0, 0) << std::endl;
    }
}

void Geometry::generateModuleLUTs(void) {
    std::vector<std::array<uint64_t, 3> > luts;
    int fe_module;
    float x, z_local = 0, r_true, phi_true, z_true, width;
    LUTEntry<uint64_t> r(&rParams), z(&zParams), phi(&phiParams);
    int length = modules.size();
    if (modules.size() == 0) getData();
    length = modules.size();
    for (auto module: modules) {
        uint64_t entry = 0;
        width = module.getWidth();
        ExactCorrection corrector(&module);
        uint64_t r_bits;
        uint64_t phi_bits;
        uint64_t z_bits;
        uint64_t layer = module.getLayer() & 0x3;
        uint64_t barrel = 0x0 & 0x1;
        uint64_t module_type = module.getModule_type() & 0x1;
        for (fe_module = 0; fe_module < 8; fe_module++) {
            x = (2*fe_module + 1) * width/16 - width/2;
            r.setExact(corrector.r(x, z_local));
            r.generateBits(0xfff);
            phi.setExact(module.getPhi() + corrector.phi(x, z_local));
            phi.generateBits(0x1ffff);
            z.setExact(module.getZ() + corrector.z(x, z_local));
            z.generateBits(0xfff);
            z.setBits((z.getExact() < 0) ? setBit(z.getBits(), 11) : z.getBits());
            entry = r.getBits() | (z.getBits() << 12) | (phi.getBits() << 24) | (layer << 44) | (barrel << 46) | (module_type << 47); 
            luts.push_back({entry & 0x3fff, (entry >> 18) & 0x3ffff, (entry >> 36) & 0x3ffff});
        }
    }
    std::array<std::ofstream, 3> lut_files;
    for (int i = 0; i < 3; i++) {
        lut_files[i].open(path + "modules_" + std::to_string(i) + ".mif");
    }
    for (auto lut : luts) {
        for (int i = 0; i < 3; i++) {
            lut_files[i] << "0x" << std::setw(5) << std::setfill('0') << std::hex << lut[i] << std::endl;
        }
    }
    for (int i = 0; i < 3; i++) {
        lut_files[i].close();
    }
    return;
}


void Geometry::generateCorrectionLUTs(void) {
    std::vector<std::array<uint64_t, 2> > luts;
    int fe_module;
    float x, z = 0, r_true, phi_true, z_true, width;
    float xgranularity, zgranularity;
    LUTEntry<uint64_t> rinv(&phiParams), cosbeta(&zParams), sinbeta(&rParams), sintheta(&rParams);
    LUTEntry<uint64_t> sinbeta_rsquared(&phiParams);
    if (modules.size() == 0) getData();
    for (auto module: modules) {
        uint64_t entry = 0;
        width = module.getWidth();
        xgranularity = module.getWidth()/1024;
        zgranularity = module.getLength()/16;
        ExactCorrection corrector(&module);
        uint64_t r_bits;
        uint64_t phi_bits;
        uint64_t z_bits;
        for (fe_module = 0; fe_module < 8; fe_module++) {
            r_true = corrector.r(x, z);
            x = (2*fe_module + 1) * width/16 - width/2;
            rinv.setExact(xgranularity/r_true);
            rinv.generateBits(0x3f);
            cosbeta.setExact(zgranularity*cos(module.getTilt_angle()));
            cosbeta.generateBits(0x3f);
            sinbeta.setExact(zgranularity*sin(module.getTilt_angle()));
            sinbeta.generateBits(0x3f);
            sintheta.setExact(xgranularity*sin(atan(x/module.getR())));
            sintheta.generateBits(0x3f);
            sinbeta_rsquared.setExact(xgranularity*zgranularity*sin(module.getTilt_angle())/(r_true*r_true));
            sinbeta_rsquared.generateBits(0x3f);
            entry = sintheta.getBits() | (sinbeta.getBits() << 6) | (rinv.getBits() << 12) | (sinbeta_rsquared.getBits() << 18) | (cosbeta.getBits() << 24); 
            luts.push_back({entry & 0x3fff, (entry >> 18) & 0x3ffff});
        }
    }
    std::array<std::ofstream, 2> lut_files;
    for (int i = 0; i < 2; i++) {
        lut_files[i].open(path + "correction_" + std::to_string(i) + ".mif");
    }
    for (auto lut : luts) {
        for (int i = 0; i < 2; i++) {
            lut_files[i] << "0x" << std::setw(5) << std::setfill('0') << std::hex << lut[i] << std::endl;
        }
    }
    for (int i = 0; i < 2; i++) {
        lut_files[i].close();
    }
    return;
}