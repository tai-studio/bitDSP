// author: Till Bovermann
// license: GPL2+
// year: 2020

DBitShift : DUGen {
	*new { arg in = 0, num = 1, wrap = 0;
		^this.multiNew('demand', in, num, wrap)
	}
}