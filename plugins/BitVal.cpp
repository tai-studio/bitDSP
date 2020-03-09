// BitVal.cpp
// author: LFSaw (Till Bovermann)
// website: http://tai-studio.org
//          http://lfsaw.de
// license: GPL2+
// year: 2020


#include "SC_PlugIn.hpp"
#include "BitVal.hpp"
// #include <iostream>

static InterfaceTable* ft;

namespace bitDSP {

BitVal::BitVal() {
    if (isAudioRateIn(0)) {
        mCalcFunc = make_calc_function<BitVal, &BitVal::next_a>();
        next_a(1);
    } else {
        mCalcFunc = make_calc_function<BitVal, &BitVal::next_k>();
        next_k(1);
    }
}

void BitVal::next_k(int nSamples) {
    float in = in0(0);
    float* fp_output = out(0);

    bit16 bit_out = (uint16) in;
    float f_out = b2f(bit_out);
    for (int i=0; i < nSamples; ++i){
        fp_output[i] = f_out;
    }
}

void BitVal::next_a(int nSamples) {
    const float* fp_input = in(0);
    float* fp_output = out(0);

    for (int i = 0; i < nSamples; ++i) {
        float32 in = fp_input[i];
        bit16 bit_out = (uint16) in;
        fp_output[i] = b2f(bit_out);
    }
}


} // namespace bitDSP

PluginLoad(bitDSPUGens) {
    // Plugin magic
    ft = inTable;
    registerUnit<bitDSP::BitVal>(ft, "BitVal");
}
