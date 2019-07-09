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
#include <regex>

#include "constants.hpp"
#include "commonfuncs.hpp"

class Module {
private:
    std::vector<std::string> string_paramaters;
    int id;
    std::string section;
    int layer;
    int ring;
    float r;
    float z;
    float tilt_angle;
    float phi;
    float width;
    float length;
    float spacing;
    float thickness;
    int module_type;

public:
    Module(std::vector<std::string> params);
    virtual ~Module(void);

    void print(void);

    std::vector<std::string> getString_paramaters(void);
    void setString_paramaters(std::vector<std::string> Module_string_paramaters);
    int getId(void);
    void setId(int Module_id);
    std::string getSection(void);
    void setSection(std::string Module_section);
    int getLayer(void);
    void setLayer(int Module_layer);
    int getRing(void);
    void setRing(int Module_ring);
    float getR(void);
    void setR(float Module_r);
    float getZ(void);
    void setZ(float Module_z);
    float getTilt_angle(void);
    void setTilt_angle(float Module_tilt_angle);
    float getPhi(void);
    void setPhi(float Module_phi);
    float getWidth(void);
    void setWidth(float Module_width);
    float getLength(void);
    void setLength(float Module_length);
    float getSpacing(void);
    void setSpacing(float Module_spacing);
    float getThickness(void);
    void setThickness(float Module_thickness);
    int getModule_type(void);
    void setModule_type(int Module_module_type);
};
