#pragma once

#include <string>
#include <sstream>
#include <cstring>
#include <fstream>
#include <iostream>
#include <cstdint>
#include <ios>
#include <array>
#include <vector>

#include "constants.hpp"
#include "commonfuncs.hpp"
#include "Module.hpp"
#include "NonantAssigment.hpp"

class Geometry {
private:
    std::ifstream datafile;
    std::vector<Module> modules;

public:
    Geometry(void);
    virtual ~Geometry(void);

    std::vector<std::string> splitLine(std::string line);
    std::vector<Module> getData(void);
    void runNonantAssignment(void);

    std::vector<Module> getModules(void);
    void setModules(std::vector<Module> Geometry_modules);

};
