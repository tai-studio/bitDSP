// author: Till Bovermann
// license: GPL2+
// year: 2020

DIBitShifter : DUGen {
	*new { arg in = 0, fb = 0, resetval = 0;
		^this.multiNew('demand', in, fb, resetval)
	}
}