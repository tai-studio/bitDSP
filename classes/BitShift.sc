// author: Till Bovermann
// license: GPL2+
// year: 2020

BitShift : UGen {
	*ir { |in, num = 0, wrap = 0|
		^this.multiNew('scalar', in, num, wrap);
	}
	*ar { |in, num = 0, wrap = 0|
		^this.multiNew('audio', in, num, wrap);
	}
	*kr { |in, num = 0, wrap = 0|
		^this.multiNew('control', in, num, wrap);
	}
	// signalRange { ^\unipolar }
	checkInputs {
		/* TODO */
		^this.checkValidInputs;
	}
}
