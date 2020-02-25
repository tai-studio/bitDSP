// author: Till Bovermann
// license: GPL2+
// year: 2020

DIBitVal : DUGen {
	*new { arg in1 = 0, in2 = 0, mask = 0;
		^this.multiNew('demand', in1, in2, mask)
	}
}
