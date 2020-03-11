s.reboot

// BitDAC

(
// huom! selection of kr/ar for time-varying parameters has significant effect on calculated artifacts
// the exact position of e.g. the appearance of new values (when does rounding happen wrt. other parameters?) causes bit-glitches
{
	var size_ar, offset_ar;
	var size_kr, offset_kr;
	var bit_kr = BitVal.ir(2r0101010101010101);
	var bit_ar = BitVal.ar(2r0101010101010101);
	size_ar = SinOsc.ar(20, 1).range(1, 16).round(1);
	size_kr = SinOsc.kr(20, 1).range(1, 16).round(1);
	offset_ar = SinOsc.ar(20, 0).range(1, 16).round(1);
	offset_kr = SinOsc.kr(20, 0).range(1, 16).round(1);

	[

		BitDAC.ar(bit_kr, size_kr, offset_kr), // kkk
		BitDAC.ar(bit_ar, size_kr, offset_kr), // akk
		BitDAC.ar(bit_kr, size_ar, offset_ar), // kaa
		BitDAC.ar(bit_ar, size_ar, offset_ar), // aaa
		BitDAC.ar(bit_kr, size_ar, offset_kr), // kak
		BitDAC.ar(bit_ar, size_ar, offset_kr), // aak
		BitDAC.ar(bit_kr, size_kr, offset_ar), // kka
		BitDAC.ar(bit_ar, size_kr, offset_ar), // aka
	]

	}.plot(0.1);
)



// Bit*


BitVal




// BitNot
{BitPrint.kr(BitNot.kr(BitVal.kr(2r0)), Impulse.kr(0))}.plot(0.01)
// bit: 2r1111111111111111
{BitPrint.ar(BitNot.ar(BitVal.ar(2r0)), Impulse.ar(0))}.plot(0.01)
// bit: 2r1111111111111111

// BitAnd
{BitPrint.kr(BitAnd.kr(BitVal.kr(2r0110), BitVal.kr(2r1010)), Impulse.kr(0))}.plot(0.1)
// bit: 2r0000000000000010
{BitPrint.ar(BitAnd.ar(BitVal.ar(2r0110), BitVal.ar(2r1010)), Impulse.ar(0))}.plot(0.1)
// bit: 2r0000000000000010

// BitOr
{BitPrint.kr(BitOr.kr(BitVal.kr(2r0110), BitVal.kr(2r1010)), Impulse.kr(0))}.plot(0.1)
// bit: 2r0000000000001110
{BitPrint.ar(BitOr.ar(BitVal.ar(2r0110), BitVal.ar(2r1010)), Impulse.ar(0))}.plot(0.1)
// bit: 2r0000000000001110

// BitXor
{BitPrint.kr(BitXor.kr(BitVal.kr(2r0110), BitVal.kr(2r1010)), Impulse.kr(0))}.plot(0.1)
// bit: 2r0000000000001100
{BitPrint.ar(BitXor.ar(BitVal.ar(2r0110), BitVal.ar(2r1010)), Impulse.ar(0))}.plot(0.1)
// bit: 2r0000000000001100

// BitSort
{BitPrint.kr(BitSort.kr(BitVal.kr(2r0110)), Impulse.kr(0))}.plot(0.01)
// bit: 2r0000000000000011
{BitPrint.ar(BitSort.ar(BitVal.ar(2r0110)), Impulse.ar(0))}.plot(0.01)
// bit: 2r0000000000000011

// BitScramble
{RandSeed.ir(123); BitPrint.kr(BitScramble.kr(BitVal.kr(2r01111111110)), Impulse.kr(0))}.plot(0.01)
// bit: 2r0110011100100111
{RandSeed.ir(123); BitPrint.ar(BitScramble.ar(BitVal.ar(2r01111111110)), Impulse.ar(0))}.plot(0.01)
// bit: 2r0110011100100111



// DBit*
( // DBitVal — without mask
{var trig = Impulse.ar(0); BitPrint.ar(
	TDemand.ar(trig, 0, demandUGens: DBitVal(in: 2r1111111111111111)),
	trig)
}.plot(0.01)
// bit: 2r1111111111111101
)

( // DBitVal — with optional mask
{var trig = Impulse.ar(0); BitPrint.ar(
	TDemand.ar(trig, 0, demandUGens: DBitVal(in: 2r1111111111111111, mask: BitVal.ir(2r1111111111111101))),
	trig)
}.plot(0.01)
// bit: 2r1111111111111101
)


( // DBitAnd with optional mask
{var trig = Impulse.ar(0); BitPrint.ar(
	TDemand.ar(trig, 0, demandUGens: DBitAnd(BitVal.ir(2r01100110), BitVal.ir(2r10101010), mask: BitVal.ir(2r11110000))),
	trig)
}.plot(0.01)
// bit: 2r0000000000100110
)

( // DBitOr with optional mask
{var trig = Impulse.ar(0); BitPrint.ar(
	TDemand.ar(trig, 0, demandUGens: DBitOr(BitVal.ir(2r01100110), BitVal.ir(2r10101010), mask: BitVal.ir(2r11110000))),
	trig)
}.plot(0.01)
// bit: 2r0000000011100110
)

( // DBitXor with optional mask
{var trig = Impulse.ar(0); BitPrint.ar(
	TDemand.ar(trig, 0, demandUGens: DBitXor(BitVal.ir(2r01100110), BitVal.ir(2r10101010), mask: BitVal.ir(2r11110000))),
	trig)
}.plot(0.01)
// bit: 2r0000000011000110
)

( // DBitNot with optional mask
{var trig = Impulse.ar(0); BitPrint.ar(
	TDemand.ar(trig, 0, demandUGens: DBitNot(BitVal.ir(2r01100110), mask: BitVal.ir(2r11110000))),
	trig)
}.plot(0.01)
// bit: 2r0000000010010110
)

( // DBitSort
{var trig = Impulse.ar(0); BitPrint.ar(
	TDemand.ar(trig, 0, demandUGens: DBitSort(BitVal.ir(2r01100110))),
	trig)
}.plot(0.01)
// bit: 2r0000000000001111
)


s.reboot
( // DBitScramble
{var trig = Impulse.ar(0); RandSeed.ir(12356); BitPrint.ar(
	TDemand.ar(trig, 0, demandUGens: DBitScramble(BitVal.ir(2r01100110))),
	trig)
}.plot(0.01)
// bit: 2r0011000000101000
)



// DBitShifter
( // negative hop
{var trig = Impulse.ar(100); BitPrint.ar(
	TDemand.ar(trig, 0, demandUGens: DBitShifter(0, -1, 0, BitVal.ir(2r1111111111111111))),
	trig)
}.plot(0.15)
// bit:
)

( // positive hop
{var trig = Impulse.ar(100); BitPrint.ar(
	TDemand.ar(trig, 0, demandUGens: DBitShifter(0, 1, 0, BitVal.ir(2r1))),
	trig)
}.plot(0.15)
// bit:
)

( // positive hop > 1
{var trig = Impulse.ar(100); BitPrint.ar(
	TDemand.ar(trig, 0, demandUGens: DBitShifter(0, 2, 0, BitVal.ir(2r1))),
	trig)
}.plot(0.15)
// bit:
)


( // positive hop > 1 & wrap == 1
{var trig = Impulse.ar(100); BitPrint.ar(
	TDemand.ar(trig, 0, demandUGens: DBitShifter(BitVal.ir(2r1), 2, 1, BitVal.ir(2r1))),
	trig)
}.plot(0.15)
// bit:
)


( // positive hop > 1 & wrap == 0
{var trig = Impulse.ar(100); BitPrint.ar(
	TDemand.ar(trig, 0, demandUGens: DBitShifter(BitVal.ir(2r1011111111111111), 3, 0, BitVal.ir(2r1))),
	trig)
}.plot(0.15)
// bit:
)

////////////////////////////////////////////////////////////

/// DBitLFSR


// due to compute optimisation (one less shift operation needed), LFSR works with left-shift rather than (common) right-shift operations. I.e., values travel right-to-left and polynomial (polynome indeces) need to be read from right to to left: x^16 + x^15 + x^14 + ... + x^1
(
{var trig = Impulse.ar(300); BitPrint.ar(
	TDemand.ar(trig, 0, demandUGens: DBitLFSR(
		mask:     BitVal.ir(2r1011010000000000),
		resetval: BitVal.ir(2r11)
	)),
	trig)
}.plot(0.15)
// bit:
)

Ndef(\lfsr).edit
(
Ndef(\lfsr).addSpec(\tFreq, [1, 10000, \exp]);
Ndef(\lfsr, {
	var tFreq = \tFreq.kr(100);
	var trig = Impulse.ar(tFreq);
	var bits = Demand.ar(trig, 0, demandUGens: DBitLFSR(
		// mask:     BitVal.ir(2r1011010000000000), // maximum period
		mask:     BitVal.ir(2r1011110000000000), // very much smaller period
		resetval: BitVal.ir(2r11)
	));

	BitDAC.ar(bits, 16).range(-1, 1)!2;
})
)


1772
1770
1585
1583
1581 // longer period
1580
1577
1571
1567
1437


16
17
18
19
20
21

(
Ndef(\lfsr).addSpec(\tFreq, [1, 10000, \exp]);
Ndef(\lfsr).addSpec(\reset, [0, 1, \lin, 1]);
Ndef(\lfsr).addSpec(\polynomial, [0, 65535, \lin, 1]); // you'll never hit all of them with a slider
Ndef(\lfsr, {
	var polynomial = \polynomial.kr(0);
	var reset = \reset.tr(0);
	var seed = BitVal.altering(2r1101101101101011);
	var tFreq = \tFreq.kr(100);
	var trig = Impulse.ar(tFreq);
	var bits = Demand.ar(
		trig: trig,
		reset: reset,
		demandUGens: DBitLFSR(
			mask:     BitVal.kr(polynomial),
			resetval: polynomial
		)
	);

	BitDAC.ar(bits, 16).range(-1, 1)!2;
})
)



(
Ndef(\lfsr).addSpec(\tFreq, [1, 10000, \exp]);
Ndef(\lfsr).addSpec(\reset, [0, 1, \lin, 1]);
Ndef(\lfsr).addSpec(\polynomial, [0, 65535, \lin, 1]); // you'll never hit all of them with a slider
Ndef(\lfsr, {
	var polynomial = \polynomial.kr(0);
	var reset = \reset.tr(0);
	var seed = IRand(0, 65535).poll(0);
	var tFreq = \tFreq.kr(100);
	var trig = Impulse.ar(tFreq);
	var bits = Demand.ar(
		trig: trig,
		reset: reset,
		demandUGens: DBitLFSR(
			mask:     BitVal.kr(polynomial),
			resetval: BitVal.kr(seed)
		)
	);

	BitDAC.ar(bits, 16).range(-1, 1)!2;
})
)



(
Ndef(\lfsr).addSpec(\tFreq, [1, 10000, \exp]);
Ndef(\lfsr).addSpec(\reset, [0, 1, \lin, 1]);
Ndef(\lfsr).addSpec(\polynomial, [0, 65535, \lin, 1]); // you'll never hit all of them with a slider, try <shift>+<up/down> in the NdefGUI numberbox...
Ndef(\lfsr, {
	var polynomial = LFNoise0.ar(50).range(16, 1220).round(1);
	var reset = \reset.tr(0);
	var seed = IRand(0, 65535).poll(0);
	var tFreq = \tFreq.kr(100);
	var trig = Impulse.ar(tFreq);
	var bits = Demand.ar(
		trig: trig,
		reset: reset,
		demandUGens: DBitLFSR(
			mask:     BitVal.ar(polynomial),
			resetval: BitVal.kr(seed)
		)
	);

	LeakDC.ar(BitDAC.ar(bits, 16).range(-1, 1))!2;
})
)


var num = 2r10100111;
(num bitXor: (num >> 1)).asBinaryString(16);


Ndef(\a, {
	var val = MouseX.kr(0, 65535);
	var trig = Changed.kr(val, 0);
	BitPrint.kr(BitVal.kr(val), Impulse.kr(10))
})


////////////////////////////////////////////////////////////

(
// right-shift
var i_hop = 5;
var bit_state = 2r1111111111111111;
(((1<<i_hop)-1) & bit_state).asBinaryString(16)
)

(
// left-shift
var i_hop = 5;
var bit_state = 2r1111111111111111;
(((16rffff)<<(16-i_hop)) & bit_state >> (16-i_hop)).asBinaryString(16)
)

(16rffff).asBinaryString(16)