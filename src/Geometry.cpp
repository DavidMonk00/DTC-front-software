#include "Geometry.hpp"

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
    int cic;
    float x, z = 0, r_true, phi_true, z_true, width;
    int length = modules.size();
    if (modules.size() == 0) getData();
    length = modules.size();
    for (auto module: modules) {
        width = module.getWidth();
        ExactCorrection corrector(&module);
        int r_bits;
        std::vector<int> phi_bits;
        std::vector<int> z_bits;
        for (cic = 0; cic < 8; cic++) {
            x = (2*cic + 1) * width/16 - width/2;
            r_true = corrector.r(x, z);
            r_bits = (int)(r_true/rParams.getBasis()) & 0xfff;
            phi_true = module.getPhi() + corrector.phi(x, z);
            phi_bits.push_back(phi_true/phiParams.getBasis());
            z_true = module.getZ() + corrector.z(x, z);
            z_bits.push_back(z_true/zParams.getBasis());
            z_true = module.getZ();
        }

    }
    return;
}