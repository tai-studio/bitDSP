// BitNot.cpp
// author: LFSaw (Till Bovermann)
// website: http://tai-studio.org
//          http://lfsaw.de
// license: GPL2+
// year: 2020


#include "SC_PlugIn.hpp"
#include "BitNot.hpp"
#include <iostream>

static InterfaceTable* ft;

namespace bitDSP {

BitNot::BitNot() {
    mCalcFunc = make_calc_function<BitNot, &BitNot::next_a>();
    next_a(1);
}

void BitNot::next_a(int nSamples) {
    const float* input = in(0);
    float32 fVal; // current value in float representation
    bit16 iVal; // current value in integer representation
    float* outbuf = out(0);
    uint32 outVal;
    

    for (int i = 0; i < nSamples; ++i) {
        fVal = input[i];
        iVal = (uint16) *(uint32*)&fVal; // direct cast

        // std::cout << "nIn: " << iVal.to_string() << '\n';

        outVal = (uint32) (iVal.flip()).to_ulong();
        outbuf[i] = *(float32*)&outVal; // direct cast from uint32 to float32
    }
}


} // namespace bitDSP

PluginLoad(bitDSP) {
    // Plugin magic
    ft = inTable;
    registerUnit<bitDSP::BitNot>(ft, "BitNot");
}
