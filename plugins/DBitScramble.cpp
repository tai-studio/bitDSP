// name: "DBitScramble"
// author: LFSaw (Till Bovermann)
// website: http://tai-studio.org
//          http://lfsaw.de
// license: GPL2+
// year: 2020
// algorithm after 
// https://stackoverflow.com/questions/57316214/efficiently-randomly-shuffling-the-bits-of-a-sequence-of-words

#include "SC_PlugIn.h"
#include "bitDSP.h"
// #include <iostream>

// InterfaceTable contains pointers to functions in the host (server).
static InterfaceTable *ft;

// namespace bitDSP {

typedef unsigned int uint;
// declare struct to hold unit generator state
struct DBitScramble : public Unit
{
};


// declare unit generator functions

void DBitScramble_Ctor(DBitScramble *unit);
void DBitScramble_Dtor(DBitScramble *unit);
void DBitScramble_next(DBitScramble *unit, int inNumSamples);

//////////////// DBitScramble //////////////////////////////////////////////


void DBitScramble_Ctor(DBitScramble *unit)
{
    SETCALC(DBitScramble_next);

    DBitScramble_next(unit, 0);
    OUT0(0) = 0;
}

void DBitScramble_Dtor(DBitScramble *unit)
{
    // unit->~DBitScramble();
}

void DBitScramble_next(DBitScramble *unit, int inNumSamples)
{

    if (inNumSamples) {// calc samples
        const float32 f_in    = DEMANDINPUT_A(0, inNumSamples);
        const bit16 bit_in  = bitDSP::f2b(f_in); // direct cast;
        RGen& rgen = *unit->mParent->mRGen; // random generator
        bit16 bit_out = 0;

        if (bit_in.all()) {
            bit_out = bit_in;
        } else {
            int i_num = bit_in.count();
            for (int i = 0; i_num; ++i) { // i_num is changed in loop
                int x = rgen.irand(15-i); // random value between 0 and 16-i-1
                if (x < i_num) {
                    bit_out.set(i);
                    --i_num;
                }
            }
        }

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
    // DefineDtorUnit(bitDSP::DBitScramble);
    DefineDtorUnit(DBitScramble);
}