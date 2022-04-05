(
s.options.device = "Fireface UFX (23610321)";
s.options.memSize = 32768;
s.reboot;
)


s.sampleRate

// 24000/2/2/2/2/2/2/3/5/5/5

(
Ndef(\a).addSpec(\sRate, [1, 24000, \exp, 1]);
Ndef(\a, {|sRate = 24000|
	var trig = Impulse.ar(sRate)!2;
	var val;
	val = trig.collect{|t| Demand.ar(t, 0, demandUGens: DBitLFSR(
		mask:     BitVal.ir(2r1011010000000000),
		resetval: BitVal.ir(2r11)
	))};

	BitDAC.ar(val, 16, 0).range(-1, 1)
})
)


NdefMixer(s)



// modulate sRate to create a snare

(
Ndef(\bitSnare).addSpec(\sRate, [1, 24000, \exp, 1]);
Ndef(\bitSnare, {|sRate = 24000, dur = 0.1|
	var sRateEnv = Env.perc(0, dur, sRate, \curve.kr(-4)).ar(gate: K2A.ar(\trig.tr(0)));
	var trig = Impulse.ar(sRateEnv);
	var val;
	val = Demand.ar(trig, 0, demandUGens: DBitLFSR(
		mask:     BitVal.ir(2r1011010000000000),
		resetval: BitVal.ir(2r11)
	));

	BitDAC.ar(val, 16, 0).range(-1, 1) !2
})
)

Ndef(\bitSnare).set(\sRate, 12000, \trig, 1, \dur, 0.01, \curve, -5)


// self-modulate sRate

(
Ndef(\bitMod).addSpec(
	\wet, [0, 1],
	\t60, [0.1, 60, \exp],
	\damp, [0, 1],
	\size, [0.5, 3],
	\earlydiff, [0, 1],
	\mdepth, [0, 50],
	\mfreq, [0, 10],
	\lowx, [0, 1],
	\midx, [0, 1],
	\highx, [0, 1],
	\lowband, [100, 6000, \exp],
	\highband, [1000, 10000, \exp]
);

Ndef(\bitMod, {
	var lIn = LocalIn.ar(2, 1);
	var sRates = lIn.linexp(-1, 1, 200, 1000);
	var trigs = Impulse.ar(sRates);
	var vals, verb;

	vals = trigs.collect{|trig, i|
		Demand.ar(trig, 0, demandUGens: DBitLFSR(
			// mask:     BitVal.ir(2r1011010000000000), // max
			mask:     BitVal.ir(2r1010010000110100),
			resetval: [BitVal.ir(2r11), BitVal.ir(2r111)][i]
		));
	};

	vals = BitDAC.ar(vals, 16, 0).range(-1, 1);
	LocalOut.ar(vals);

	vals = RLPF.ar(vals, \lpFreq.kr(50), \lpRq.kr(2));
	vals = Splay.ar([vals[0], vals.sum, vals[1]], 0.5) * 0.3;

	verb = JPverb.ar(vals, \t60.kr(1,           0.05),
        \damp.kr(0,          0.05),
        \size.kr(1,          0.05),
        \earlydiff.kr(0.707, 0.05),
        \mdepth.kr(5,        0.05),
        \mfreq.kr(2,         0.05),
        \lowx.kr(1,          0.05),
        \midx.kr(1,          0.05),
        \highx.kr(1,         0.05),
        \lowband.kr(500,     0.05),
        \highband.kr(2000,   0.05)
	);

	SelectX.ar(\wet.kr(0), [vals, verb])

})
)