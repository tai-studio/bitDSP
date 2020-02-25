// BitAnd.hpp
// author: LFSaw (Till Bovermann)
// website: http://tai-studio.org
//          http://lfsaw.de
// license: GPL2+
// year: 2020


#pragma once

#include "SC_PlugIn.hpp"
#include "bitDSP.h"

namespace bitDSP {


class BitAnd : public SCUnit {
public:
    BitAnd();

    // Destructor
    // ~BitAnd();

private:
    // Calc functions
    void next_aa(int nSamples);
    void next_ak(int nSamples);
    void next_ka(int nSamples);
    void next_kk(int nSamples);

    // Member variables
};

} // namespace bitDSP
