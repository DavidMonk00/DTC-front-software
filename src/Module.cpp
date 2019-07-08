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

void Module::setString_paramaters(std::vector<std::string> Module_string_paramaters) {
	string_paramaters = Module_string_paramaters;
}

int Module::getId(void) {
	return id;
}

void Module::setId(int Module_id) {
	id = Module_id;
}

std::string Module::getSection(void) {
	return section;
}

void Module::setSection(std::string Module_section) {
	section = Module_section;
}

int Module::getLayer(void) {
	return layer;
}

void Module::setLayer(int Module_layer) {
	layer = Module_layer;
}

int Module::getRing(void) {
	return ring;
}

void Module::setRing(int Module_ring) {
	ring = Module_ring;
}

float Module::getR(void) {
	return r;
}

void Module::setR(float Module_r) {
	r = Module_r;
}

float Module::getZ(void) {
	return z;
}

void Module::setZ(float Module_z) {
	z = Module_z;
}

float Module::getTilt_angle(void) {
	return tilt_angle;
}

void Module::setTilt_angle(float Module_tilt_angle) {
	tilt_angle = Module_tilt_angle;
}

float Module::getPhi(void) {
	return phi;
}

void Module::setPhi(float Module_phi) {
	phi = Module_phi;
}

float Module::getWidth(void) {
	return width;
}

void Module::setWidth(float Module_width) {
	width = Module_width;
}

float Module::getLength(void) {
	return length;
}

void Module::setLength(float Module_length) {
	length = Module_length;
}

float Module::getSpacing(void) {
	return spacing;
}

void Module::setSpacing(float Module_spacing) {
	spacing = Module_spacing;
}

float Module::getThickness(void) {
	return thickness;
}

void Module::setThickness(float Module_thickness) {
	thickness = Module_thickness;
}
