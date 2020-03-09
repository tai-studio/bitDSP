// author: Till Bovermann
// license: GPL2+
// year: 2020

DBitVal : DUGen {
	*new { arg in, mask;
		mask = mask ?? {BitVal.ir(2r1111111111111111)};
		^this.multiNew('demand', in, mask)
	}
}
