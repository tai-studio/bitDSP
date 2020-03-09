// author: Till Bovermann
// license: GPL2+
// year: 2020

DBitNot : DUGen {
	*new { arg in = 0, mask;
		mask = mask ?? {BitVal.ir(2r1111111111111111)};
		^this.multiNew('demand', in, mask)
	}
}

