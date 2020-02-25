// BitPrint.cpp
// author: LFSaw (Till Bovermann)
// website: http://tai-studio.org
//          http://lfsaw.de
// license: GPL2+
// year: 2020


#include "SC_PlugIn.hpp"
#include "BitPrint.hpp"
#include <iostream>

static InterfaceTable* ft;

namespace bitDSP {

BitPrint::BitPrint() {
    m_trig = 0.;

    if (isAudioRateIn(0)) {
        // std::cout << "audio\n";

        mCalcFunc = make_calc_function<BitPrint, &BitPrint::next_a>();
        next_a(1);

    } else {
        // std::cout << "control\n";

        mCalcFunc = make_calc_function<BitPrint, &BitPrint::next>();
        next(1);
    }
}

void BitPrint::next(int nSamples) {
    float in = in0(0);
    float trig = in0(1);
    float *outbuf = out(0);
    // std::cout << "ctl\t" << m_trig << "\t" << trig << '\n';

    if (trig > 0.f && m_trig <= 0.f) {
        const bit16 bIn = (uint16) *(uint32*)&in; // direct cast
        std::cout << "bit: " << bIn.to_string() << '\n';
    }
    m_trig = trig;

    for (int i=0; i < nSamples; ++i){
        outbuf[i] = in;
    }
}

void BitPrint::next_a(int nSamples) {
    const float* input = zin(0);
    const float* trig = zin(1);
    float* outbuf = out(0);
    
    float prevtrig = m_trig;

    for (int i = 0; i < nSamples; ++i) {
        float32      in = ZXP(input);
        float32 curtrig = ZXP(trig);

        if (curtrig > 0.f && prevtrig <= 0.f) {
            bit16 bIn = (uint16) *(uint32*)&in; // direct cast
            std::cout << "bit: " << bIn.to_string() << '\n';
        } prevtrig = curtrig;

        outbuf[i] = in;
    }
}


} // namespace bitDSP

PluginLoad(bitDSP) {
    // Plugin magic
    ft = inTable;
    registerUnit<bitDSP::BitPrint>(ft, "BitPrint");
}
