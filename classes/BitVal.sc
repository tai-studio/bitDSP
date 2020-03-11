// author: Till Bovermann
// license: GPL2+
// year: 2020

BitVal : UGen {
	*max {
		^this.ir(2r1111111111111111)		
	}
	*min {
		^this.ir(0)		
	}
	*altering {
		^this.ir(2r0101010101010101)		
	}
	*gray{|in|
		var val;
		switch (in.rate, 
			\scalar,	{
				val = this.ir(in); 
				^BitXor.ar(val, BitShift.ir(val, -1 /* right shift */))
			}, 
			\audio,	{
				val = this.ar(in); 
				^BitXor.ar(val, BitShift.ar(val, -1 /* right shift */))
			},
			\control,	{
				val = this.kr(in); 
				^BitXor.ar(val, BitShift.kr(val, -1 /* right shift */))
			}
		)
	}
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
