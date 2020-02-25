// BitXor.hpp
// author: LFSaw (Till Bovermann)
// website: http://tai-studio.org
//          http://lfsaw.de
// license: GPL2+
// year: 2020


#pragma once

#include "SC_PlugIn.hpp"
#include "bitDSP.h"

namespace bitDSP {


class BitXor : public SCUnit {
public:
    BitXor();

    // Destructor
    // ~BitXor();

private:
    // Calc function, audio
    void next_a(int nSamples);

    // Member variables
};

} // namespace bitDSP