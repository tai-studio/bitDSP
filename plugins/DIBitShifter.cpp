// name: "DIBitShifter"
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


namespace bitDSP {

typedef unsigned int uint;
// declare struct to hold unit generator state
struct DIBitShifter : public Unit
{
    bit16 state;
};


// declare unit generator functions

void DIBitShifter_Ctor(DIBitShifter *unit);
void DIBitShifter_Dtor(DIBitShifter *unit);
void DIBitShifter_next(DIBitShifter *unit, int inNumSamples);

//////////////// DIBitShifter //////////////////////////////////////////////


void DIBitShifter_Ctor(DIBitShifter *unit)
{
    SETCALC(DIBitShifter_next);

    unit->state = 0;

    DIBitShifter_next(unit, 0);
    // printf("initial state: %d,\n", unit->state);
    OUT0(0) = 0;
}

void DIBitShifter_Dtor(DIBitShifter *unit)
{
    // unit->~DIBitShifter();
}

void DIBitShifter_next(DIBitShifter *unit, int inNumSamples)
{
    const float32 in    = DEMANDINPUT_A(0, inNumSamples);
    const float32 fb    = DEMANDINPUT_A(1, inNumSamples);
    
    if (inNumSamples) {// calc samples
        bit16 x = unit->state;

        bool lsbs = x.test(15); // keep bit to be shifted out


        // 1. central shift operation
        // bitwise rotate
        x <<= 1;

        
        // 2. set input
        if (fb > 0){ // feed lost bit back in
            x.set(0, lsbs);
        } else { // set to input
            x.set(0, in>0);
        }

        unit->state = x;
        // std::cout << "bSh: " << x.to_string() << '\n';        // printf("\n");

        // uint32 ui_out = (uint32) x.to_ulong();
        // OUT0(0) = *(float32*)&ui_out; // direct cast from uint32 to float32
        OUT0(0) = b2f(x);

    } else { // reset
        float32 fState = DEMANDINPUT_A(2, inNumSamples);
        // bit16 initialState = ;

        // unit->state = (uint16) *(uint32*)&(fState);
        unit->state = f2b(fState);

        RESETINPUT(0);
        RESETINPUT(1);
        // RESETINPUT(2); // do not reset the initialState slot?
    }
}

} // namespace bitDSP

//////////////////////////////
PluginLoad(bitDSP)
{
    // InterfaceTable *inTable implicitly given as argument to load function
    ft = inTable;
    DefineDtorUnit(bitDSP::DIBitShifter);
}