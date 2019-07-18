#include "Module.hpp"

Module::Module(std::vector<std::string> params) {
    setId(std::stoi(params[0]));
    setSection(params[2]);
    setLayer(std::stoi(params[3]));
    setRing(std::stoi(params[4]));
    setR(std::stof(params[5]));
    setZ(std::stof(params[6]));
    setTilt_angle(std::stof(params[7]));
    setPhi(std::stof(params[9]));
    setWidth(std::stof(params[10]));
    setLength(std::stof(params[11]));
    setSpacing(std::stof(params[12]));
    setThickness(std::stof(params[13]));

    std::regex reg_2s("(.*)(2S)(.*)");
    std::regex reg_ec("(.*)(D_1)(.*)");
    setModule_type(
        std::regex_match(getSection(), reg_2s) ||
        std::regex_match(getSection(), reg_ec)
    );
}

Module::~Module(void) {}

void Module::print(void) {
    std::cout << "----- Module -----" << '\n';
    std::cout << "ID: " << getId() << '\n';
    std::cout << "Section: " << getSection() << '\n';
    std::cout << "Layer: " << getLayer() << '\n';
    std::cout << "Ring: " << getRing() << '\n';
    std::cout << "r (mm): " << getR() << '\n';
    std::cout << "z (mm): " << getZ() << '\n';
    std::cout << "Tilt Angle (degrees): " << getTilt_angle() << '\n';
    std::cout << "Phi (degrees): " << getPhi() << '\n';
    std::cout << "Width (mm): " << getWidth() << '\n';
    std::cout << "Length (mm): " << getLength() << '\n';
    std::cout << "Spacing (mm): " << getSpacing() << '\n';
    std::cout << "Thickness (mm): " << getThickness() << '\n';
}

std::vector<std::string> Module::getString_paramaters(void) {
	return string_paramaters;
}

void Module::setString_paramaters(std::vector<std::string> string_paramaters) {
	this->string_paramaters = string_paramaters;
}

int Module::getId(void) {
	return id;
}

void Module::setId(int id) {
	this->id = id;
}

std::string Module::getSection(void) {
	return section;
}

void Module::setSection(std::string section) {
	this->section = section;
}

int Module::getLayer(void) {
	return layer;
}

void Module::setLayer(int layer) {
	this->layer = layer;
}

int Module::getRing(void) {
	return ring;
}

void Module::setRing(int ring) {
	this->ring = ring;
}

float Module::getR(void) {
	return r;
}

void Module::setR(float r) {
	this->r = r;
}

float Module::getZ(void) {
	return z;
}

void Module::setZ(float z) {
	this->z = z;
}

float Module::getTilt_angle(void) {
	return tilt_angle;
}

void Module::setTilt_angle(float tilt_angle) {
	this->tilt_angle = tilt_angle;
}

float Module::getPhi(void) {
	return phi;
}

void Module::setPhi(float phi) {
	this->phi = phi;
}

float Module::getWidth(void) {
	return width;
}

void Module::setWidth(float width) {
	this->width = width;
}

float Module::getLength(void) {
	return length;
}

void Module::setLength(float length) {
	this->length = length;
}

float Module::getSpacing(void) {
	return spacing;
}

void Module::setSpacing(float spacing) {
	this->spacing = spacing;
}

float Module::getThickness(void) {
	return thickness;
}

void Module::setThickness(float thickness) {
	this->thickness = thickness;
}

int Module::getModule_type(void) {
    return module_type;
}

void Module::setModule_type(int Module_module_type) {
    this->module_type = module_type;
}
