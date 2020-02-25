// author: Till Bovermann
// license: GPL2+
// year: 2020

BitPrint : UGen {
	*ir { |input|
		^this.multiNew('scalar', input, 1);
	}
	*ar { |input, trig|
		^this.multiNew('audio', input, trig);
	}
	*kr { |input, trig|
		^this.multiNew('control', input, trig);
	}
	checkInputs {
		/* TODO */
		^this.checkValidInputs;
	}
}
