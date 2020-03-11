// author: Till Bovermann
// license: GPL2+
// year: 2020

DBitLFSR : DUGen {
	*new { arg mask = 0, resetval = 1;
		^this.multiNew('demand', mask, resetval)
	}
}