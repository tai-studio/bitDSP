// name: "DBitShifter"
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
struct DBitShifter : public Unit
{
    bit16 m_state;
};


// declare unit generator functions

void DBitShifter_Ctor(DBitShifter *unit);
void DBitShifter_Dtor(DBitShifter *unit);
void DBitShifter_next(DBitShifter *unit, int inNumSamples);

//////////////// DBitShifter //////////////////////////////////////////////


void DBitShifter_Ctor(DBitShifter *unit)
{
    SETCALC(DBitShifter_next);

    unit->m_state = 0;

    DBitShifter_next(unit, 0);
    // printf("initial state: %d,\n", unit->m_state);
    OUT0(0) = 0;
}

void DBitShifter_Dtor(DBitShifter *unit)
{
    // unit->~DBitShifter();
}

void DBitShifter_next(DBitShifter *unit, int inNumSamples)
{
    const float32 f_input = DEMANDINPUT_A(0, inNumSamples);
    int i_hop   = (int) DEMANDINPUT_A(1, inNumSamples);
    const float32 f_wrap  = DEMANDINPUT_A(2, inNumSamples);
    
    if (inNumSamples) {// calc samples
        bit16 bit_state = unit->m_state;
 
        bit16 bit_fill;
        // 2. set input
        if (f_wrap > 0){ // feed in lost bits
            bit_fill = bit_state;
        } else { // feed in input
            bit_fill = bitDSP::f2b(f_input);
        }

        if (i_hop >= 0) { 
            // left-shift
            bit_state <<= i_hop;

            // fill with material
            int i_invHop = 16-i_hop;
            bit_fill = (bit16(0xffff) << i_invHop) & bit_fill;
            bit_fill >>= i_invHop;
        } else { 
            // i_hop *= -1;
            i_hop = -i_hop;
            // right-shift
            bit_state >>= i_hop;

            // fill with material
            bit_fill = (bit16(0xffff) >> i_hop) & bit_fill;
            bit_fill <<= i_hop;
        }
        bit_state |=  bit_fill;

         unit->m_state = bit_state;
        // std::cout << "bSh: " << bit_state.to_string() << '\n';        // printf("\n");

        // uint32 ui_out = (uint32) bit_state.to_ulong();
        // OUT0(0) = *(float32*)&ui_out; // direct cast from uint32 to float32
        OUT0(0) = bitDSP::b2f(bit_state);

    } else { // reset
        float32 f_state = DEMANDINPUT_A(3, inNumSamples);
        // bit16 initialState = ;

        // unit->state = (uint16) *(uint32*)&(f_state);
        unit->m_state = bitDSP::f2b(f_state);

        RESETINPUT(0);
        RESETINPUT(1);
        RESETINPUT(2);
        // RESETINPUT(3); // do not reset the initialState slot?
    }
}

// } // namespace bitDSP

//////////////////////////////
PluginLoad(bitDSPUGens)
{
    // InterfaceTable *inTable implicitly given as argument to load function
    ft = inTable;
    // DefineDtorUnit(bitDSP::DBitShifter);
    DefineDtorUnit(DBitShifter);
}