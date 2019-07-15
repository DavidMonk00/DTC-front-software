#pragma once

#include <cstdint>

#include "constants.hpp"

template <class T>
class LUTEntry {
private:
    Parameters* params;
    float exact;
    T bits;
public:
    LUTEntry(Parameters* entry_params);
    ~LUTEntry(void);
    Parameters* getParams(void);
    void setParams(Parameters* entry_params);
    float getExact(void);
    void setExact(float exact_value);
    T getBits(void);
    void setBits(T entry_bits);
    void generateBits(int mask);
};

template <class T>
LUTEntry<T>::LUTEntry(Parameters* entry_params) {
    params = entry_params;
}

template <class T>
LUTEntry<T>::~LUTEntry(void) {}

template <class T>
float LUTEntry<T>::getExact(void) {
    return exact;
}

template <class T>
void LUTEntry<T>::setExact(float exact_value) {
    exact = exact_value;
}

template <class T>
T LUTEntry<T>::getBits(void) {
    return bits;
}

template <class T>
void LUTEntry<T>::setBits(T entry_bits) {
    bits = entry_bits;
}

template <class T>
Parameters* LUTEntry<T>::getParams(void) {
    return params;
}

template <class T>
void LUTEntry<T>::setParams(Parameters* entry_params) {
    params = entry_params;
}

template <class T>
void LUTEntry<T>::generateBits(int mask) {
    bits = (T)((int)(exact/params->getBasis()) & mask);
}