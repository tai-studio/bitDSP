// author: Till Bovermann
// license: GPL2+
// year: 2020

DBitShifter : DUGen {
	*new { arg in = 0, hop = 1, wrap = 0, resetval = 0;
		^this.multiNew('demand', in, hop, wrap, resetval)
	}
}