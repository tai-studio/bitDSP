// author: Till Bovermann
// license: GPL2+
// year: 2020

DBitXor : DUGen {
	*new { arg in1 = 0, in2 = 0, mask;
		mask = mask ?? {BitVal.ir(2r1111111111111111)};
		^this.multiNew('demand', in1, in2, mask)
	}
}
