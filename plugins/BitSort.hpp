// BitSort.hpp
// author: LFSaw (Till Bovermann)
// website: http://tai-studio.org
//          http://lfsaw.de
// license: GPL2+
// year: 2020


#pragma once

#include "SC_PlugIn.hpp"
#include "bitDSP.h"

namespace bitDSP {


class BitSort : public SCUnit {
public:
    BitSort();

    // Destructor
    // ~BitSort();

private:
    // Calc functions
    void next_a(int nSamples);
    void next_k(int nSamples);

    // Member variables
};

} // namespace bitDSP
