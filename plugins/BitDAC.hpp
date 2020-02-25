// BitDAC.hpp
// author: LFSaw (Till Bovermann)
// website: http://tai-studio.org
//          http://lfsaw.de
// license: GPL2+
// year: 2020


#pragma once

#include "SC_PlugIn.hpp"
#include "bitDSP.h"

namespace bitDSP {

class BitDAC : public SCUnit {
public:
    BitDAC();

    // Destructor
    // ~BitDAC();

private:

    // Calc functions
    void next_aaa(int nSamples);
    void next_aak(int nSamples);
    void next_aka(int nSamples);
    void next_akk(int nSamples);
    void next_kaa(int nSamples);
    void next_kak(int nSamples);
    void next_kka(int nSamples);
    void next_kkk(int nSamples);

    // Member variables
};

} // namespace bitDSP
