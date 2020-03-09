// BitSort.cpp
// author: LFSaw (Till Bovermann)
// website: http://tai-studio.org
//          http://lfsaw.de
// license: GPL2+
// year: 2020


#include "SC_PlugIn.hpp"
#include "BitSort.hpp"
// #include <iostream>

static InterfaceTable* ft;

namespace bitDSP {

BitSort::BitSort() {
    if (isAudioRateIn(0)) { // a
        mCalcFunc = make_calc_function<BitSort, &BitSort::next_a>();
        next_a(1);
    } else {
        mCalcFunc = make_calc_function<BitSort, &BitSort::next_k>();
        next_k(1);
    }
}

void BitSort::next_a(int nSamples) {
    const float* fp_input = in(0);
    float* fp_output = out(0);

    for (int i = 0; i < nSamples; ++i) {
        float32 f_in = fp_input[i];
        bit16 bit_in = f2b(f_in); // direct cast

        // ui_out = ((1<<bit_in.count())-1);
        // fp_output[i] = *(float32*)&ui_out; // direct cast from uint32 to float32
        fp_output[i] = b2f(((1<<bit_in.count())-1));
    }
}

void BitSort::next_k(int nSamples) {
    const float f_in = in0(0);
    float* fp_output = out(0);

    bit16 bit_in = f2b(f_in); // direct cast
    float32 f_out = b2f( (1<<bit_in.count())-1 );
    for (int i = 0; i < nSamples; ++i) {
        fp_output[i] = f_out;
    }
}

} // namespace bitDSP

PluginLoad(bitDSPUGens) {
    // Plugin magic
    ft = inTable;
    registerUnit<bitDSP::BitSort>(ft, "BitSort");
}
