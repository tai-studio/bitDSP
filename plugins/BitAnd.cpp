// BitAnd.cpp
// author: LFSaw (Till Bovermann)
// website: http://tai-studio.org
//          http://lfsaw.de
// license: GPL2+
// year: 2020

#include "SC_PlugIn.hpp"
#include "BitAnd.hpp"

static InterfaceTable* ft;

namespace bitDSP {

BitAnd::BitAnd() {
    if (isAudioRateIn(0)) { // ax
        if (isAudioRateIn(1)) { // aa
            mCalcFunc = make_calc_function<BitAnd, &BitAnd::next_aa>();
            next_aa(1);
        } else { // ak
            mCalcFunc = make_calc_function<BitAnd, &BitAnd::next_ak>();
            next_ak(1);
        }
    } else { // kx
        if (isAudioRateIn(1)) { // ka
            mCalcFunc = make_calc_function<BitAnd, &BitAnd::next_ka>();
            next_ka(1);
        } else { // ak
            mCalcFunc = make_calc_function<BitAnd, &BitAnd::next_kk>();
            next_kk(1);
        }
    }

}

void BitAnd::next_aa(int nSamples) {
    const float* fp_input1 = in(0);
    const float* fp_input2 = in(1);
    float* fp_output = out(0);

    for (int i = 0; i < nSamples; ++i) {
        float32 f_in1 = fp_input1[i];
        bit16 bit_in1 = f2b(f_in1); // direct cast
        float32 f_in2 = fp_input2[i];
        bit16 bit_in2 = f2b(f_in2); // direct cast

        fp_output[i] = b2f(bit_in1 & bit_in2);
    }
}

void BitAnd::next_ak(int nSamples) {
    const float* fp_input1 = in(0);
    const float f_in2 = in0(1);
    float* fp_output = out(0);

    bit16 bit_in2 = f2b(f_in2); // direct cast

    for (int i = 0; i < nSamples; ++i) {
        float32 f_in1 = fp_input1[i];
        bit16 bit_in1 = f2b(f_in1); // direct cast

        fp_output[i] = b2f(bit_in1 & bit_in2);
    }
}

void BitAnd::next_ka(int nSamples) {
    const float f_in1 = in0(0);
    const float* fp_input2 = in(1);
    float* fp_output = out(0);

    bit16 bit_in1 = f2b(f_in1); // direct cast

    for (int i = 0; i < nSamples; ++i) {
        float32 f_in2 = fp_input2[i];
        bit16 bit_in2 = f2b(f_in2); // direct cast

        fp_output[i] = b2f(bit_in1 & bit_in2);
    }
}

void BitAnd::next_kk(int nSamples) {
    const float f_in1 = in0(0);
    const float f_in2 = in0(1);
    float* fp_output = out(0);

    bit16 bit_in1 = f2b(f_in1); // direct cast
    bit16 bit_in2 = f2b(f_in2); // direct cast
    float32 f_out = b2f(bit_in1 & bit_in2);
    for (int i = 0; i < nSamples; ++i) {

        fp_output[i] = f_out;
    }
}

} // namespace bitDSP

PluginLoad(bitDSPUGens) {
    // Plugin magic
    ft = inTable;
    registerUnit<bitDSP::BitAnd>(ft, "BitAnd");
}
