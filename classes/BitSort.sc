// author: Till Bovermann
// license: GPL2+
// year: 2020

BitSort : UGen {
	*ir { |in|
		^this.multiNew('scalar', in);
	}
	*ar { |in|
		^this.multiNew('audio', in);
	}
	*kr { |in|
		^this.multiNew('control', in);
	}
	// signalRange { ^\unipolar }
	checkInputs {
		/* TODO */
		^this.checkValidInputs;
	}
}
