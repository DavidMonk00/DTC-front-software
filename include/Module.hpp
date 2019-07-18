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
    void setString_paramaters(std::vector<std::string> string_paramaters);
    int getId(void);
    void setId(int id);
    std::string getSection(void);
    void setSection(std::string section);
    int getLayer(void);
    void setLayer(int layer);
    int getRing(void);
    void setRing(int ring);
    float getR(void);
    void setR(float r);
    float getZ(void);
    void setZ(float z);
    float getTilt_angle(void);
    void setTilt_angle(float tilt_angle);
    float getPhi(void);
    void setPhi(float phi);
    float getWidth(void);
    void setWidth(float width);
    float getLength(void);
    void setLength(float length);
    float getSpacing(void);
    void setSpacing(float spacing);
    float getThickness(void);
    void setThickness(float thickness);
    int getModule_type(void);
    void setModule_type(int module_type);
};
