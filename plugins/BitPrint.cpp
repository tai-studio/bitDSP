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
    float f_input = in0(0);
    float f_trig = in0(1);
    float *fp_output = out(0);
    // std::cout << "ctl\t" << m_trig << "\t" << f_trig << '\n';

    if (f_trig > 0.f && m_trig <= 0.f) {
        const bit16 bit_in = f2b(f_input); // direct cast
        std::cout << "bit: " << bit_in.to_string() << '\n';
    }
    m_trig = f_trig;

    for (int i=0; i < nSamples; ++i){
        fp_output[i] = f_input;
    }
}

void BitPrint::next_a(int nSamples) {
    const float* fp_input = zin(0);
    const float* fp_trig = zin(1);
    float* fp_output = out(0);
    
    float prevtrig = m_trig;

    for (int i = 0; i < nSamples; ++i) {
        float32      in = ZXP(fp_input);
        float32 curtrig = ZXP(fp_trig);

        if (curtrig > 0.f && prevtrig <= 0.f) {
            bit16 bit_in = f2b(in); // direct cast
            std::cout << "bit: " << bit_in.to_string() << '\n';
        } prevtrig = curtrig;

        fp_output[i] = in;
    }
}


} // namespace bitDSP

PluginLoad(bitDSP) {
    // Plugin magic
    ft = inTable;
    registerUnit<bitDSP::BitPrint>(ft, "BitPrint");
}
