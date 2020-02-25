// author: Till Bovermann
// license: GPL2+
// year: 2020

BitDAC : UGen {
	*ir { |in, size = 1, offset = 0|
		^this.multiNew('scalar', in, size, offset);
	}
	*ar { |in, size = 1, offset = 0|
		^this.multiNew('audio', in, size, offset);
	}
	*kr { |in, size = 1, offset = 0|
		^this.multiNew('control', in, size, offset);
	}
	signalRange { ^\unipolar }
	checkInputs {
		/* TODO */
		^this.checkValidInputs;
	}
}
