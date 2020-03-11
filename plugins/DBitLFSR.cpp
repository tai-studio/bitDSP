// name: "DBitLFSR"
// author: LFSaw (Till Bovermann)
// website: http://tai-studio.org
//          http://lfsaw.de
// license: GPL2+
// year: 2020

#include "SC_PlugIn.h"
#include "bitDSP.h"
// #include <iostream>

// InterfaceTable contains pointers to functions in the host (server).
static InterfaceTable *ft;


// namespace bitDSP {

typedef unsigned int uint;
// declare struct to hold unit generator state
struct DBitLFSR : public Unit
{
    bit16 m_state;
};


// declare unit generator functions

void DBitLFSR_Ctor(DBitLFSR *unit);
void DBitLFSR_Dtor(DBitLFSR *unit);
void DBitLFSR_next(DBitLFSR *unit, int inNumSamples);

//////////////// DBitLFSR //////////////////////////////////////////////


void DBitLFSR_Ctor(DBitLFSR *unit)
{
    SETCALC(DBitLFSR_next);

    unit->m_state = 0;

    DBitLFSR_next(unit, 0);
    // printf("initial state: %d,\n", unit->m_state);
    OUT0(0) = 0;
}

void DBitLFSR_Dtor(DBitLFSR *unit)
{
    // unit->~DBitLFSR();
}

void DBitLFSR_next(DBitLFSR *unit, int inNumSamples)
{
   const float32 f_mask = DEMANDINPUT_A(0, inNumSamples);
    // int i_hop   = (int) DEMANDINPUT_A(1, inNumSamples);
    // const float32 f_wrap  = DEMANDINPUT_A(2, inNumSamples);
    
    if (inNumSamples) {// calc samples
        bit16 bit_state = unit->m_state;
        bit16 bit_mask = bitDSP::f2b(f_mask);

        // mask deselected bits
        uint16 ui_op = (bit_state & bit_mask).to_ulong();
        
        // find parity of 16bit bitset, 
        // adapted from https://graphics.stanford.edu/~seander/bithacks.html#ParityParallel
        ui_op ^= ui_op >> 8;
        ui_op ^= ui_op >> 4;
        ui_op &= 0xf;
        bit16 bit_in = (0x6996 >> ui_op) & 1;

        // shift
        bit_state <<= 1;

        // set new bit
        bit_state |= bit_in;

        unit->m_state = bit_state;
        OUT0(0) = bitDSP::b2f(bit_state);

    } else { // reset
        float32 f_state = DEMANDINPUT_A(1, inNumSamples);
        // bit16 initialState = ;

        // unit->state = (uint16) *(uint32*)&(f_state);
        unit->m_state = bitDSP::f2b(f_state);
        // std::cout << unit->m_state << "\n";
        // RESETINPUT(0);
        // RESETINPUT(1); // do not reset the initialState slot?
    }
}

// } // namespace bitDSP

//////////////////////////////
PluginLoad(bitDSPUGens)
{
    // InterfaceTable *inTable implicitly given as argument to load function
    ft = inTable;
    // DefineDtorUnit(bitDSP::DBitLFSR);
    DefineDtorUnit(DBitLFSR);
}