// BitDAC.cpp
// author: LFSaw (Till Bovermann)
// website: http://tai-studio.org
//          http://lfsaw.de
// license: GPL2+
// year: 2020


#include "SC_PlugIn.hpp"
#include "BitDAC.hpp"
// #include <iostream>

static InterfaceTable* ft;

namespace bitDSP {

BitDAC::BitDAC() {
    if (isAudioRateIn(0)) { // axx
        if (isAudioRateIn(1)) {  // aax
            if (isAudioRateIn(2)) {  // aaa
                // std::cout << "aaa" << '\n';
                mCalcFunc = make_calc_function<BitDAC, &BitDAC::next_aaa>();
                next_aaa(1);
            } else {  // aak
                // std::cout << "aak" << '\n';
                mCalcFunc = make_calc_function<BitDAC, &BitDAC::next_aak>();
                next_aak(1);
            }
        } else {  // akx
            if (isAudioRateIn(2)) { // aka
                // std::cout << "aka" << '\n';
                mCalcFunc = make_calc_function<BitDAC, &BitDAC::next_aka>();
                next_aka(1);
            } else { // akk
                // std::cout << "akk" << '\n';
                mCalcFunc = make_calc_function<BitDAC, &BitDAC::next_akk>();
                next_akk(1);
            }
        }
    } else { // kxx
        if (isAudioRateIn(1)) { // kax
            if (isAudioRateIn(2)) { // kaa
                // std::cout << "kaa" << '\n';
                mCalcFunc = make_calc_function<BitDAC, &BitDAC::next_kaa>();
                next_kaa(1);
            } else { // kak
                // std::cout << "kak" << '\n';
                mCalcFunc = make_calc_function<BitDAC, &BitDAC::next_kak>();
                next_kak(1);
            }
        } else { // kkx
            if (isAudioRateIn(2)) { // kka
                // std::cout << "kka" << '\n';
                mCalcFunc = make_calc_function<BitDAC, &BitDAC::next_kka>();
                next_kka(1);
            } else { // kkk
                // std::cout << "kkk" << '\n';
                mCalcFunc = make_calc_function<BitDAC, &BitDAC::next_kkk>();
                next_kkk(1);
            }
        }
    }
}


void BitDAC::next_kkk(int i_numSamples) {
    const float f_input  = in0(0);
    const float f_size   = in0(1);
    const float f_offset = in0(2);
    float* fp_output = out(0);
    
    int i_size       = static_cast<int>(f_size);
    int i_offset     = static_cast<int>(f_offset);


    float32 f_in  = f_input;
    bit16 bit_in  = f2b(f_in); // direct cast into bit16

    uint16 ui_maxVal = (1 << i_size)-1; // maximum value that fits into i_size
    bit16 bit_mask   = ui_maxVal << i_offset; // mask selects area

    bit16 bit_out    = (bit_in & bit_mask) >> i_offset; // shift selection to right-most bits

    float32 f_out    = static_cast<float32>(
        static_cast<double>(bit_out.to_ulong()) 
      / static_cast<double>(ui_maxVal)
    ); // normalise

    f_out = zapgremlins(f_out);

    // std::cout << fp_output[i] << '\t' << ui_maxVal << '\t' << i_offset << '\t' << i_size << '\n';
    for (int i = 0; i < i_numSamples; ++i) {
        fp_output[i] = f_out;
    }
}

void BitDAC::next_aaa(int i_numSamples) {
    const float* fp_input = in(0);
    const float* fp_size = in(1);
    const float* fp_offset = in(2);
    float* fp_output = out(0);
    
    for (int i = 0; i < i_numSamples; ++i) {
        float32 f_in = fp_input[i];
        bit16 bit_in = f2b(f_in); // direct cast into bit16


        int i_offset     = static_cast<int>(fp_offset[i]);
        int i_size       = static_cast<int>(fp_size[i]);

        uint16 ui_maxVal = (1 << i_size)-1; // maximum value that fits into i_size

        bit16 bit_mask   = ui_maxVal << i_offset; // mask selects area
        bit16 bit_out    = (bit_in & bit_mask) >> i_offset; // shift selection to right-most bits

        float32 f_out    = 
            static_cast<float32>(
                static_cast<double>(bit_out.to_ulong()) 
              / static_cast<double>(ui_maxVal)
            ); // normalise

        fp_output[i] = zapgremlins(f_out);
        // std::cout << fp_output[i] << '\t' << ui_maxVal << '\t' << i_offset << '\t' << i_size << '\n';
    }
}


void BitDAC::next_kaa(int i_numSamples) {
    const float  f_input   = in0(0);
    const float* fp_size   = in(1);
    const float* fp_offset = in(2);
    float* fp_output = out(0);
    
    float32 f_in = f_input;
    bit16 bit_in = f2b(f_in); // direct cast into bit16

    for (int i = 0; i < i_numSamples; ++i) {
        int i_offset     = static_cast<int>(fp_offset[i]);
        int i_size       = static_cast<int>(fp_size[i]);

        uint16 ui_maxVal = (1 << i_size)-1; // maximum value that fits into i_size

        bit16 bit_mask   = ui_maxVal << i_offset; // mask selects area
        bit16 bit_out    = (bit_in & bit_mask) >> i_offset; // shift selection to right-most bits

        float32 f_out    = 
            static_cast<float32>(
                static_cast<double>(bit_out.to_ulong()) 
              / static_cast<double>(ui_maxVal)
            ); // normalise

        fp_output[i] = zapgremlins(f_out);
        // std::cout << fp_output[i] << '\t' << ui_maxVal << '\t' << i_offset << '\t' << i_size << '\n';
    }
}

void BitDAC::next_akk(int i_numSamples) {
    const float* fp_input = in(0);
    const float f_size    = in0(1);
    const float f_offset  = in0(2);
    float* fp_output = out(0);
    
    int i_size       = static_cast<int>(f_size);
    int i_offset     = static_cast<int>(f_offset);


    uint16 ui_maxVal = (1 << i_size)-1; // maximum value that fits into i_size
    bit16 bit_mask   = ui_maxVal << i_offset; // mask selects area

    for (int i = 0; i < i_numSamples; ++i) {
        float32 f_in = fp_input[i];
        bit16 bit_in = f2b(f_in); // direct cast into bit16

        bit16 bit_out    = (bit_in & bit_mask) >> i_offset; // shift selection to right-most bits

        float32 f_out    = 
            static_cast<float32>(
                static_cast<double>(bit_out.to_ulong()) 
              / static_cast<double>(ui_maxVal)
            ); // normalise

        fp_output[i] = zapgremlins(f_out);

        // std::cout << fp_output[i] << '\t' << ui_maxVal << '\t' << i_offset << '\t' << i_size << '\n';

    }
}

void BitDAC::next_kka(int i_numSamples) {
    const float  f_input   = in0(0);
    const float  f_size    = in0(1);
    const float* fp_offset = in(2);
    float* fp_output = out(0);
    
    float32 f_in = f_input;
    bit16 bit_in = f2b(f_in); // direct cast into bit16

    int i_size       = static_cast<int>(f_size);
    uint16 ui_maxVal = (1 << i_size)-1; // maximum value that fits into i_size

    for (int i = 0; i < i_numSamples; ++i) {
        int i_offset     = static_cast<int>(fp_offset[i]);


        bit16 bit_mask   = ui_maxVal << i_offset; // mask selects area
        bit16 bit_out    = (bit_in & bit_mask) >> i_offset; // shift selection to right-most bits

        float32 f_out    = 
            static_cast<float32>(
                static_cast<double>(bit_out.to_ulong()) 
              / static_cast<double>(ui_maxVal)
            ); // normalise

        fp_output[i] = zapgremlins(f_out);
        // std::cout << fp_output[i] << '\t' << ui_maxVal << '\t' << i_offset << '\t' << i_size << '\n';
    }
}

////////////////









void BitDAC::next_kak(int i_numSamples) {
    const float  f_input   = in0(0);
    const float* fp_size   = in(1);
    const float  f_offset  = in0(2);
    float* fp_output = out(0);
    
    float32 f_in = f_input;
    bit16 bit_in = f2b(f_in); // direct cast into bit16

    int i_offset     = static_cast<int>(f_offset);

    for (int i = 0; i < i_numSamples; ++i) {
        int i_size       = static_cast<int>(fp_size[i]);

        uint16 ui_maxVal = (1 << i_size)-1; // maximum value that fits into i_size

        bit16 bit_mask   = ui_maxVal << i_offset; // mask selects area
        bit16 bit_out    = (bit_in & bit_mask) >> i_offset; // shift selection to right-most bits

        float32 f_out    = 
            static_cast<float32>(
                static_cast<double>(bit_out.to_ulong()) 
              / static_cast<double>(ui_maxVal)
            ); // normalise

        fp_output[i] = zapgremlins(f_out);
        // std::cout << fp_output[i] << '\t' << ui_maxVal << '\t' << i_offset << '\t' << i_size << '\n';
    }
}

void BitDAC::next_aka(int i_numSamples) {
    const float* fp_input  = in(0);
    const float  f_size    = in0(1);
    const float* fp_offset = in(2);
    float* fp_output = out(0);
    
    int i_size       = static_cast<int>(f_size);
    uint16 ui_maxVal = (1 << i_size)-1; // maximum value that fits into i_size

    for (int i = 0; i < i_numSamples; ++i) {
        float32 f_in = fp_input[i];
        bit16 bit_in = f2b(f_in); // direct cast into bit16

        int i_offset     = static_cast<int>(fp_offset[i]);

        bit16 bit_mask   = ui_maxVal << i_offset; // mask selects area
        bit16 bit_out    = (bit_in & bit_mask) >> i_offset; // shift selection to right-most bits

        float32 f_out    = 
            static_cast<float32>(
                static_cast<double>(bit_out.to_ulong()) 
              / static_cast<double>(ui_maxVal)
            ); // normalise

        fp_output[i] = zapgremlins(f_out);

        // std::cout << fp_output[i] << '\t' << ui_maxVal << '\t' << i_offset << '\t' << i_size << '\n';

    }
}

void BitDAC::next_aak(int i_numSamples) {
    const float* fp_input = in(0);
    const float* fp_size = in(1);
    const float f_offset = in0(2);
    float* fp_output = out(0);
    
    int i_offset     = static_cast<int>(f_offset);

    for (int i = 0; i < i_numSamples; ++i) {
        float32 f_in = fp_input[i];
        bit16 bit_in = f2b(f_in); // direct cast into bit16


        int i_size       = static_cast<int>(fp_size[i]);

        uint16 ui_maxVal = (1 << i_size)-1; // maximum value that fits into i_size

        bit16 bit_mask   = ui_maxVal << i_offset; // mask selects area
        bit16 bit_out    = (bit_in & bit_mask) >> i_offset; // shift selection to right-most bits

        float32 f_out    = 
            static_cast<float32>(
                static_cast<double>(bit_out.to_ulong()) 
              / static_cast<double>(ui_maxVal)
            ); // normalise

        fp_output[i] = zapgremlins(f_out);

        // std::cout << fp_output[i] << '\t' << ui_maxVal << '\t' << i_offset << '\t' << i_size << '\n';

    }
}






} // namespace bitDSP

PluginLoad(bitDSPUGens) {
    // Plugin magic
    ft = inTable;
    registerUnit<bitDSP::BitDAC>(ft, "BitDAC");
}
