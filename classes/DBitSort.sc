// author: Till Bovermann
// license: GPL2+
// year: 2020

DBitSort : DUGen {
	*new { arg in;
		^this.multiNew('demand', in)
	}
}
