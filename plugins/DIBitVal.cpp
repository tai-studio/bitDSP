// name: "DIBitVal"
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
typedef unsigned int uint;
// declare struct to hold unit generator state
struct DIBitVal : public Unit
{
};


// declare unit generator functions

void DIBitVal_Ctor(DIBitVal *unit);
void DIBitVal_Dtor(DIBitVal *unit);
void DIBitVal_next(DIBitVal *unit, int inNumSamples);

//////////////// DIBitVal //////////////////////////////////////////////


void DIBitVal_Ctor(DIBitVal *unit)
{
    SETCALC(DIBitVal_next);

    DIBitVal_next(unit, 0);
    OUT0(0) = 0;
}

void DIBitVal_Dtor(DIBitVal *unit)
{
    // unit->~DIBitVal();
}

void DIBitVal_next(DIBitVal *unit, int inNumSamples)
{
    
    if (inNumSamples) {// calc samples
        const float32 in = DEMANDINPUT_A(0, inNumSamples);
        bit16 bOut;

        bOut = (uint16) in;

        // std::cout << "val: " << bOut.to_string() << '\n';

        uint32 outVal = (uint32) (bOut).to_ulong();
        OUT0(0) = *(float32*)&outVal; // direct cast from uint32 to float32
    } else { // reset
        // bubble up reset
        RESETINPUT(0);
    }
}



//////////////////////////////
PluginLoad(bitDSP)
{
    // InterfaceTable *inTable implicitly given as argument to load function
    ft = inTable;
    DefineDtorUnit(DIBitVal);
}