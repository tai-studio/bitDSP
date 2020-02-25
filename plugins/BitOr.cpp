// BitOr.cpp
// author: LFSaw (Till Bovermann)
// website: http://tai-studio.org
//          http://lfsaw.de
// license: GPL2+
// year: 2020

#include "SC_PlugIn.hpp"
#include "BitOr.hpp"

static InterfaceTable* ft;

namespace bitDSP {

BitOr::BitOr() {
    mCalcFunc = make_calc_function<BitOr, &BitOr::next_a>();
    next_a(1);
}

void BitOr::next_a(int nSamples) {
    const float* input1 = in(0);
    const float* input2 = in(1);
    float32 fVal1; // current value in float representation
    bit16 iVal1; // current value in integer representation
    float32 fVal2; // current value in float representation
    bit16 iVal2; // current value in integer representation
    float* outbuf = out(0);
    uint32 outVal;


    for (int i = 0; i < nSamples; ++i) {
        fVal1 = input1[i];
        iVal1 = (uint16) *(uint32*)&fVal1; // direct cast
        fVal2 = input2[i];
        iVal1 = (uint16) *(uint32*)&fVal2; // direct cast
        outVal = (uint32) (iVal1 | iVal2).to_ulong();
        outbuf[i] = *(float32*)&outVal; // direct cast from ulong to float64, then cast to float32
    }
}


} // namespace bitDSP

PluginLoad(bitDSP) {
    // Plugin magic
    ft = inTable;
    registerUnit<bitDSP::BitOr>(ft, "BitOr");
}
