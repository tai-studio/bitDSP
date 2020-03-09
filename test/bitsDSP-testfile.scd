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