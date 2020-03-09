// name: "DBitNot"
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
struct DBitNot : public Unit
{
};


// declare unit generator functions

void DBitNot_Ctor(DBitNot *unit);
void DBitNot_Dtor(DBitNot *unit);
void DBitNot_next(DBitNot *unit, int inNumSamples);

//////////////// DBitNot //////////////////////////////////////////////


void DBitNot_Ctor(DBitNot *unit)
{
    SETCALC(DBitNot_next);

    DBitNot_next(unit, 0);
    OUT0(0) = 0;
}

void DBitNot_Dtor(DBitNot *unit)
{
    // unit->~DBitNot();
}

void DBitNot_next(DBitNot *unit, int inNumSamples)
{
    
    if (inNumSamples) {// calc samples
        const float32 f_in    = DEMANDINPUT_A(0, inNumSamples);
        const float32 f_mask  = DEMANDINPUT_A(1, inNumSamples);
        const bit16 bit_in  = bitDSP::f2b(f_in); // direct cast;
        const bit16 bit_mask = bitDSP::f2b(f_mask); // direct cast;

        bit16 bit_out = ~bit_in; // process
        // apply only to selected bits, leave rest alonw
        bit_out = (bit_mask & bit_out) | (~bit_mask & bit_in); 

        OUT0(0) = bitDSP::b2f(bit_out);
    } else { // reset
        // bubble up reset
        RESETINPUT(0);
        RESETINPUT(1);
    }
}

// } // namespace bitDSP


//////////////////////////////
PluginLoad(bitDSPUGens)
{
    // InterfaceTable *inTable implicitly given as argument to load function
    ft = inTable;
    // DefineDtorUnit(bitDSP::DBitNot);
    DefineDtorUnit(DBitNot);
}