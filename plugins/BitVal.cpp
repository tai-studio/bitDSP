// BitVal.cpp
// author: LFSaw (Till Bovermann)
// website: http://tai-studio.org
//          http://lfsaw.de
// license: GPL2+
// year: 2020


#include "SC_PlugIn.hpp"
#include "BitVal.hpp"
#include <iostream>

static InterfaceTable* ft;

namespace bitDSP {

BitVal::BitVal() {
    if (isAudioRateIn(0)) {
        // std::cout << "audio\n";
        mCalcFunc = make_calc_function<BitVal, &BitVal::next_a>();
        next_a(1);
    } else {
        // std::cout << "val control\n";

        mCalcFunc = make_calc_function<BitVal, &BitVal::next>();
        next(1);
    }
}

void BitVal::next(int nSamples) {
    float in = in0(0);
    float* outbuf = out(0);

    bit16 bOut = (uint16) in;
    uint32 outVal = (uint32) (bOut).to_ulong();
    for (int i=0; i < nSamples; ++i){
        outbuf[i] = *(float32*)&outVal; // direct cast from uint32 to float32
        // std::cout << "val: " << outVal << '\n';
    }
}

void BitVal::next_a(int nSamples) {
    const float* input = in(0);
    float* outbuf = out(0);

    for (int i = 0; i < nSamples; ++i) {
        float32 in = input[i];
        bit16 bOut = (uint16) in;

        uint32 outVal = (uint32) (bOut).to_ulong();
        outbuf[i] = *(float32*)&outVal; // direct cast from uint32 to float32
    }
}


} // namespace bitDSP

PluginLoad(bitDSP) {
    // Plugin magic
    ft = inTable;
    registerUnit<bitDSP::BitVal>(ft, "BitVal");
}
