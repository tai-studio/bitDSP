// author: Till Bovermann
// license: GPL2+
// year: 2020

BitAnd : UGen {
	*ir { |in1, in2|
		^this.multiNew('scalar', in1, in2);
	}
	*ar { |in1, in2|
		^this.multiNew('audio', in1, in2);
	}
	*kr { |in1, in2|
		^this.multiNew('control', in1, in2);
	}
	// signalRange { ^\unipolar }
	checkInputs {
		/* TODO */
		^this.checkValidInputs;
	}
}
