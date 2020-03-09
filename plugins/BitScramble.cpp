// BitScramble.cpp
// author: LFSaw (Till Bovermann)
// website: http://tai-studio.org
//          http://lfsaw.de
// license: GPL2+
// year: 2020
// algorithm after https://stackoverflow.com/questions/57316214/efficiently-randomly-shuffling-the-bits-of-a-sequence-of-words


#include "SC_PlugIn.hpp"
#include "BitScramble.hpp"
// #include <iostream>

static InterfaceTable* ft;

namespace bitDSP {

BitScramble::BitScramble() {
    if (isAudioRateIn(0)) {
        mCalcFunc = make_calc_function<BitScramble, &BitScramble::next_a>();
        next_a(1);
    } else {
        mCalcFunc = make_calc_function<BitScramble, &BitScramble::next_k>();
        next_k(1);
    }
}

void BitScramble::next_a(int nSamples) {
    const float* fp_input = in(0);
    float* fp_output = out(0);

    RGen& rgen = *mParent->mRGen;


    for (int i = 0; i < nSamples; ++i) {
        float32 f_in = fp_input[i];
        bit16 bit_in = f2b(f_in); // direct cast
        bit16 bit_out = 0;

        if (bit_in.all()) {
            bit_out = bit_in;
        } else {
            int i_num = bit_in.count();
            for (int j = 0; i_num; ++j) { // i_num is changed in loop
                int x = rgen.irand(15-j); // random value between 0 and 16-i-1
                if (x < i_num) {
                    bit_out.set(j);
                    --i_num;
                }
            }
        }
        fp_output[i] = b2f(bit_out);
    }
}

void BitScramble::next_k(int nSamples) {
    const float f_in = in0(0);
    float* fp_output = out(0);
    RGen& rgen = *mParent->mRGen;

    bit16 bit_in = f2b(f_in); // direct cast
    bit16 bit_out = 0;
    
    if (bit_in.all()) {
        bit_out = bit_in;
    } else {
        int i_num = bit_in.count();
        for (int j = 0; i_num; ++j) { // i_num is changed in loop
            int x = rgen.irand(15-j); // random value between 0 and 16-i-1
            if (x < i_num) {
                bit_out.set(j);
                --i_num;
            }
        }
    }

    float32 f_out = b2f(bit_out);

    for (int i = 0; i < nSamples; ++i) {
        fp_output[i] = f_out;
    }
}

} // namespace bitDSP

PluginLoad(bitDSPUGens) {
    // Plugin magic
    ft = inTable;
    registerUnit<bitDSP::BitScramble>(ft, "BitScramble");
}
