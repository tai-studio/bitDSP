// name: "DBitAnd"
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
struct DBitAnd : public Unit
{
};


// declare unit generator functions

void DBitAnd_Ctor(DBitAnd *unit);
void DBitAnd_Dtor(DBitAnd *unit);
void DBitAnd_next(DBitAnd *unit, int inNumSamples);

//////////////// DBitAnd //////////////////////////////////////////////


void DBitAnd_Ctor(DBitAnd *unit)
{
    SETCALC(DBitAnd_next);

    DBitAnd_next(unit, 0);
    OUT0(0) = 0;
}

void DBitAnd_Dtor(DBitAnd *unit)
{
    // unit->~DBitAnd();
}

void DBitAnd_next(DBitAnd *unit, int inNumSamples)
{
    
    if (inNumSamples) {// calc samples
        const float32 f_in1   = DEMANDINPUT_A(0, inNumSamples);
        const float32 f_in2   = DEMANDINPUT_A(1, inNumSamples);
        const float32 f_mask  = DEMANDINPUT_A(2, inNumSamples);
        const bit16 bit_in1 = bitDSP::f2b(f_in1); // direct cast;
        const bit16 bit_in2 = bitDSP::f2b(f_in2); // direct cast;
        const bit16 bit_mask = bitDSP::f2b(f_mask); // direct cast;

        bit16 bit_out = (bit_in1 & bit_in2); // process
        // apply only to selected bits, leave rest alonw
        bit_out = (bit_mask & bit_out) | (~bit_mask & bit_in1); 

        OUT0(0) = bitDSP::b2f(bit_out);
    } else { // reset
        // bubble up reset
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
    // DefineDtorUnit(bitDSP::DBitAnd);
    DefineDtorUnit(DBitAnd);
}