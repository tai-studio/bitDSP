// BitShift.cpp
// author: LFSaw (Till Bovermann)
// website: http://tai-studio.org
//          http://lfsaw.de
// license: GPL2+
// year: 2020


#include "SC_PlugIn.hpp"
#include "BitShift.hpp"
// #include <iostream>

static InterfaceTable* ft;

namespace bitDSP {

BitShift::BitShift() {
    if (isAudioRateIn(0)) { // ax
        if (isAudioRateIn(1)) { // aa
            mCalcFunc = make_calc_function<BitShift, &BitShift::next_aa>();
            next_aa(1);
        } else { // ak
            mCalcFunc = make_calc_function<BitShift, &BitShift::next_ak>();
            next_ak(1);
        }
    } else { // kx
        if (isAudioRateIn(1)) { // ka
            mCalcFunc = make_calc_function<BitShift, &BitShift::next_ka>();
            next_ka(1);
        } else { // ak
            mCalcFunc = make_calc_function<BitShift, &BitShift::next_kk>();
            next_kk(1);
        }
    }
}

void BitShift::next_ak(int nSamples) {
    const float* fp_input = in(0);
    int i_num = (int) in0(1);
    const float f_wrap = in0(2);
    float* fp_output = out(0);

    if (f_wrap > 0) {
        for (int i = 0; i < nSamples; ++i) {
            bit16 bit_input = f2b(fp_input[i]);
            bit16 bit_fill = bit_input;
    
            if (i_num >= 0) { 
                // left-shift
                bit_input <<= i_num;
    
                // fill with material
                int i_invNum = 16-i_num;
                bit_fill = (bit16(0xffff) << i_invNum) & bit_fill;
                bit_fill >>= i_invNum;
            } else { 
                i_num = -i_num;
                // right-shift
                bit_input >>= i_num;
    
                // fill with material
                int i_invNum = 16-i_num;
                bit_fill = (bit16(0xffff) >> i_invNum) & bit_fill;
                bit_fill <<= i_invNum;
            }
            bit_input |=  bit_fill;
            fp_output[i] = b2f(bit_input);
        }
    } else {
        for (int i = 0; i < nSamples; ++i) {
            bit16 bit_input = f2b(fp_input[i]);
    
            if (i_num >= 0) { 
                // left-shift
                bit_input <<= i_num;
            } else { 
                // right-shift
                bit_input >>= -i_num;
            }
            fp_output[i] = b2f(bit_input);
        }
    }

}

void BitShift::next_aa(int nSamples) {
    const float* fp_input = in(0);
    const float* fp_num = in(1);
    const float f_wrap = in0(2);
    float* fp_output = out(0);

    if (f_wrap > 0) {
        for (int i = 0; i < nSamples; ++i) {
            bit16 bit_input = f2b(fp_input[i]);
            bit16 bit_fill = bit_input;
            int i_num = (int) fp_num[i];

            if (i_num >= 0) { 
                // left-shift
                bit_input <<= i_num;
    
                // fill with material
                int i_invNum = 16-i_num;
                bit_fill = (bit16(0xffff) << i_invNum) & bit_fill;
                bit_fill >>= i_invNum;
            } else { 
                i_num = -i_num;
                // right-shift
                bit_input >>= i_num;
    
                // fill with material
                int i_invNum = 16-i_num;
                bit_fill = (bit16(0xffff) >> i_invNum) & bit_fill;
                bit_fill <<= i_invNum;
            }
            bit_input |=  bit_fill;
            fp_output[i] = b2f(bit_input);
        }
    } else {
        for (int i = 0; i < nSamples; ++i) {
            bit16 bit_input = f2b(fp_input[i]);
            int i_num = (int) fp_num[i];
    
            if (i_num >= 0) { 
                // left-shift
                bit_input <<= i_num;
            } else { 
                // right-shift
                bit_input >>= -i_num;
            }
            fp_output[i] = b2f(bit_input);
        }
    }

}


void BitShift::next_ka(int nSamples) {
    const float f_input = in0(0);
    const float* fp_num = in(1);
    const float f_wrap = in0(2);
    float* fp_output = out(0);

    bit16 bit_input = f2b(f_input);
    if (f_wrap > 0) {
        for (int i = 0; i < nSamples; ++i) {
            bit16 bit_fill = bit_input;
            int i_num = (int) fp_num[i];
            
            if (i_num >= 0) { 
                // left-shift
                bit_input <<= i_num;
    
                // fill with material
                int i_invNum = 16-i_num;
                bit_fill = (bit16(0xffff) << i_invNum) & bit_fill;
                bit_fill >>= i_invNum;
            } else { 
                i_num = -i_num;
                // right-shift
                bit_input >>= i_num;
    
                // fill with material
                int i_invNum = 16-i_num;
                bit_fill = (bit16(0xffff) >> i_invNum) & bit_fill;
                bit_fill <<= i_invNum;
            }
            bit_input |=  bit_fill;
            fp_output[i] = b2f(bit_input);
        }
    } else {
        for (int i = 0; i < nSamples; ++i) {
            int i_num = (int) fp_num[i];
    
            if (i_num >= 0) { 
                // left-shift
                bit_input <<= i_num;
            } else { 
                // right-shift
                bit_input >>= -i_num;
            }
            fp_output[i] = b2f(bit_input);
        }
    }

}


void BitShift::next_kk(int nSamples) {
    const float f_input = in0(0);
    int i_num = (int) in0(1);
    const float f_wrap = in0(2);
    float* fp_output = out(0);

    bit16 bit_input = f2b(f_input);
    if (f_wrap > 0) {
        bit16 bit_fill = bit_input;
        if (i_num >= 0) { 
            // left-shift
            bit_input <<= i_num;

            // fill with material
            int i_invNum = 16-i_num;
            bit_fill = (bit16(0xffff) << i_invNum) & bit_fill;
            bit_fill >>= i_invNum;
        } else { 
            i_num = -i_num;
            // right-shift
            bit_input >>= i_num;

            // fill with material
            int i_invNum = 16-i_num;
            bit_fill = (bit16(0xffff) >> i_invNum) & bit_fill;
            bit_fill <<= i_invNum;
        }
        bit_input |=  bit_fill;
    } else {
        if (i_num >= 0) { 
            // left-shift
            bit_input <<= i_num;
        } else {
            // right-shift
            bit_input >>= -i_num;
        }
    }
    float f_output = b2f(bit_input);

    for (int i = 0; i < nSamples; ++i) {
        fp_output[i] = f_output;
    }
}

} // namespace bitDSP

PluginLoad(bitDSPUGens) {
    // Plugin magic
    ft = inTable;
    registerUnit<bitDSP::BitShift>(ft, "BitShift");
}
