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
