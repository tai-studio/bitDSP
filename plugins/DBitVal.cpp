// name: "DBitVal"
// author: LFSaw (Till Bovermann)
// website: http://tai-studio.org
//          http://lfsaw.de
// license: GPL2+
// year: 2020

#include "SC_PlugIn.h"
#include "bitDSP.h"
#include <iostream>

// #include <stdio.h>

// #ifndef MAXFLOAT
// # include <float.h>
// # define MAXFLOAT FLT_MAX
// #endif

// InterfaceTable contains pointers to functions in the host (server).
static InterfaceTable *ft;

// namespace bitDSP {

typedef unsigned int uint;
// declare struct to hold unit generator state
struct DBitVal : public Unit
{
};


// declare unit generator functions

void DBitVal_Ctor(DBitVal *unit);
void DBitVal_Dtor(DBitVal *unit);
void DBitVal_next(DBitVal *unit, int inNumSamples);

//////////////// DBitVal //////////////////////////////////////////////


void DBitVal_Ctor(DBitVal *unit)
{
    SETCALC(DBitVal_next);

    DBitVal_next(unit, 0);
    OUT0(0) = 0;
}

void DBitVal_Dtor(DBitVal *unit)
{
    // unit->~DBitVal();
}

void DBitVal_next(DBitVal *unit, int inNumSamples)
{
    
    if (inNumSamples) {// calc samples
        const float32 f_in = DEMANDINPUT_A(0, inNumSamples);
        const float32 f_mask  = DEMANDINPUT_A(1, inNumSamples);

        const bit16 bit_mask = bitDSP::f2b(f_mask); // direct cast;
        bit16 bit_out = (uint16) f_in;
        // apply only to selected bits
        bit_out = bit_out & bit_mask;

        // uint32 ui_out = (uint32) bit_out.to_ulong();
        // OUT0(0) = *(float32*)&ui_out; // direct cast from uint32 to float32
        OUT0(0) = bitDSP::b2f(bit_out);
    } else { // reset
        // bubble up reset
        RESETINPUT(0);
    }
}

// } // namespace bitDSP


//////////////////////////////
PluginLoad(bitDSPUGens)
{
    // InterfaceTable *inTable implicitly given as argument to load function
    ft = inTable;
    // DefineDtorUnit(bitDSP::DBitVal);
    DefineDtorUnit(DBitVal);
}