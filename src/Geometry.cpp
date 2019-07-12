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

void Geometry::setModules(std::vector<Module> Geometry_modules) {
    modules = Geometry_modules;
}

void Geometry::runNonantAssignment(void) {
    NonantAssigment assigner;
    for (auto i : modules) {
        std::cout << assigner.assignModule(i, 0.0, 0) << std::endl;
    }
}

void Geometry::generateLUTs(void) {
    std::vector<std::array<uint64_t, 3> > luts;
    int cic;
    float x, z = 0, r_true, phi_true, z_true, width;
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
        for (cic = 0; cic < 8; cic++) {
            x = (2*cic + 1) * width/16 - width/2;
            r_true = corrector.r(x, z);
            r_bits = (uint64_t)(r_true/rParams.getBasis()) & 0xfff;
            phi_true = module.getPhi() + corrector.phi(x, z);
            phi_bits = (uint64_t)(phi_true/phiParams.getBasis()) & 0x1ffff;
            z_true = module.getZ() + corrector.z(x, z);
            z_bits = (uint64_t)((int)(z_true/zParams.getBasis()) & 0xfff);
            z_bits = (z_true < 0) ? setBit(z_bits, 11) : z_bits;
            entry = r_bits | (r_bits << 12) | (phi_bits << 24) | (layer << 44) | (barrel << 46) | (module_type << 47); 
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