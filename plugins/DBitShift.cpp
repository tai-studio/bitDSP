// name: "DBitShift"
// author: LFSaw (Till Bovermann)
// website: http://tai-studio.org
//          http://lfsaw.de
// license: GPL2+
// year: 2020

#include "SC_PlugIn.h"
#include "bitDSP.h"
// #include <iostream>

static InterfaceTable *ft;


// namespace bitDSP {

typedef unsigned int uint;
// declare struct to hold unit generator state
struct DBitShift : public Unit
{
};


// declare unit generator functions

void DBitShift_Ctor(DBitShift *unit);
void DBitShift_Dtor(DBitShift *unit);
void DBitShift_next(DBitShift *unit, int inNumSamples);

//////////////// DBitShift //////////////////////////////////////////////


void DBitShift_Ctor(DBitShift *unit)
{
    SETCALC(DBitShift_next);

    DBitShift_next(unit, 0);

    OUT0(0) = 0;
}

void DBitShift_Dtor(DBitShift *unit)
{
    // unit->~DBitShift();
}

void DBitShift_next(DBitShift *unit, int inNumSamples)
{
    const float32 f_input = DEMANDINPUT_A(0, inNumSamples);
    int i_num   = (int) DEMANDINPUT_A(1, inNumSamples);
    const float32 f_wrap  = DEMANDINPUT_A(2, inNumSamples);
    
    if (inNumSamples) {// calc samples
        bit16 bit_input = bitDSP::f2b(f_input);
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

        // uint32 ui_out = (uint32) bit_state.to_ulong();
        // OUT0(0) = *(float32*)&ui_out; // direct cast from uint32 to float32
        OUT0(0) = bitDSP::b2f(bit_input);

    } else { // reset
        RESETINPUT(0);
        RESETINPUT(1);
        RESETINPUT(2);
    }
}

// } // namespace bitDSP

//////////////////////////////
PluginLoad(bitDSPUGens)
{
    // InterfaceTable *inTable implicitly given as argument to load function
    ft = inTable;
    // DefineDtorUnit(bitDSP::DBitShift);
    DefineDtorUnit(DBitShift);
}