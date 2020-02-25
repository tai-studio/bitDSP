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

namespace bitDSP {

inline bit16 f2b(float32 f_in) {
	return (uint16) *(uint32*)&f_in;
}

}