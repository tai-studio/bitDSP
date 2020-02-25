// name: "DIBitAnd"
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
struct DIBitAnd : public Unit
{
};


// declare unit generator functions

void DIBitAnd_Ctor(DIBitAnd *unit);
void DIBitAnd_Dtor(DIBitAnd *unit);
void DIBitAnd_next(DIBitAnd *unit, int inNumSamples);

//////////////// DIBitAnd //////////////////////////////////////////////


void DIBitAnd_Ctor(DIBitAnd *unit)
{
    SETCALC(DIBitAnd_next);

    DIBitAnd_next(unit, 0);
    OUT0(0) = 0;
}

void DIBitAnd_Dtor(DIBitAnd *unit)
{
    // unit->~DIBitAnd();
}

void DIBitAnd_next(DIBitAnd *unit, int inNumSamples)
{
    
    if (inNumSamples) {// calc samples
        const float32 in1   = DEMANDINPUT_A(0, inNumSamples);
        const float32 in2   = DEMANDINPUT_A(1, inNumSamples);
        const float32 mask  = DEMANDINPUT_A(2, inNumSamples);
        const bit16 bIn1 = (uint16) *(uint32*)&in1; // direct cast;
        const bit16 bIn2 = (uint16) *(uint32*)&in2; // direct cast;
        const bit16 bMask = (uint16) *(uint32*)&mask; // direct cast;
        bit16 bOut;

        bOut = (bIn1 & bIn2); // process
        bOut = (bMask & bOut) | (~bMask & bIn1); // apply only to selected bits

        uint32 outVal = (uint32) (bIn1).to_ulong();
        OUT0(0) = *(float32*)&outVal; // direct cast from uint32 to float32
    } else { // reset
        // bubble up reset
        RESETINPUT(0);
        RESETINPUT(1);
        RESETINPUT(2);
    }
}



//////////////////////////////
PluginLoad(bitDSP)
{
    // InterfaceTable *inTable implicitly given as argument to load function
    ft = inTable;
    DefineDtorUnit(DIBitAnd);
}