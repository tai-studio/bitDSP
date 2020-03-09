// bitDSP.h
// author: LFSaw (Till Bovermann)
// website: http://tai-studio.org
//          http://lfsaw.de
// license: GPL2+
// year: 2020


#pragma once

#include <bitset>
#include "SC_PlugIn.hpp"
typedef std::bitset<32> bit32;
typedef std::bitset<24> bit24;
typedef std::bitset<16> bit16;

#define BIT16MAX 65535

namespace bitDSP {

inline bit16 f2b(float32 f_in) {
	return (uint16) *(uint32*)&f_in;
}

inline float32 b2f(bit16 bit_in) {
	uint32 ui_val = (uint32) (bit_in).to_ulong();
    return *(float32*)&ui_val; // direct cast from uint32 to float32
}
}
