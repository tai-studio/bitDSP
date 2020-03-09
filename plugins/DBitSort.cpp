// name: "DBitSort"
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
struct DBitSort : public Unit
{
};


// declare unit generator functions

void DBitSort_Ctor(DBitSort *unit);
void DBitSort_Dtor(DBitSort *unit);
void DBitSort_next(DBitSort *unit, int inNumSamples);

//////////////// DBitSort //////////////////////////////////////////////


void DBitSort_Ctor(DBitSort *unit)
{
    SETCALC(DBitSort_next);

    DBitSort_next(unit, 0);
    OUT0(0) = 0;
}

void DBitSort_Dtor(DBitSort *unit)
{
    // unit->~DBitSort();
}

void DBitSort_next(DBitSort *unit, int inNumSamples)
{
    
    if (inNumSamples) {// calc samples
        const float32 f_in    = DEMANDINPUT_A(0, inNumSamples);
        const bit16 bit_in  = bitDSP::f2b(f_in); // direct cast;

        bit16 bit_out = ((1<<bit_in.count())-1); // process

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
    // DefineDtorUnit(bitDSP::DBitSort);
    DefineDtorUnit(DBitSort);
}