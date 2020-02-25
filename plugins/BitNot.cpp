// BitNot.cpp
// author: LFSaw (Till Bovermann)
// website: http://tai-studio.org
//          http://lfsaw.de
// license: GPL2+
// year: 2020


#include "SC_PlugIn.hpp"
#include "BitNot.hpp"
// #include <iostream>

static InterfaceTable* ft;

namespace bitDSP {

BitNot::BitNot() {
    if (isAudioRateIn(0)) { // a
        mCalcFunc = make_calc_function<BitNot, &BitNot::next_a>();
        next_a(1);
    } else {
        mCalcFunc = make_calc_function<BitNot, &BitNot::next_k>();
        next_k(1);
    }
}

void BitNot::next_a(int nSamples) {
    const float* fp_input = in(0);
    float* fp_output = out(0);

    for (int i = 0; i < nSamples; ++i) {
        float32 f_in = fp_input[i];
        bit16 bit_in = f2b(f_in); // direct cast

        // std::cout << "nIn: " << bit_in.to_string() << '\n';
        fp_output[i] = b2f(bit_in.flip());
    }
}

void BitNot::next_k(int nSamples) {
    const float f_in = in0(0);
    float* fp_output = out(0);

    bit16 bit_in = f2b(f_in); // direct cast
    float32 f_out = b2f(bit_in.flip());
    for (int i = 0; i < nSamples; ++i) {
        fp_output[i] = f_out;
    }
}

} // namespace bitDSP

PluginLoad(bitDSP) {
    // Plugin magic
    ft = inTable;
    registerUnit<bitDSP::BitNot>(ft, "BitNot");
}
