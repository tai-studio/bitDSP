s.reboot


{BitDAC.ar(BitVal.ir(2r1111111111111111), 16)}.plot(0.01)
{BitDAC.ar(BitVal.kr(2r1111111111111111), 16)}.plot(0.01)
{RandSeed.ir(1); BitDAC.ar(BitVal.kr(2r0101010101010101), WhiteNoise.ar().range(1, 16))}.plot(0.1);
{RandSeed.ir(1); BitDAC.ar(BitVal.ir(2r0101010101010101), WhiteNoise.ar().range(1, 16))}.plot(0.1);
{RandSeed.ir(1); BitDAC.ar(BitVal.ar(2r0101010101010101), WhiteNoise.ar().range(1, 16))}.plot(0.1);


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



{BitPrint.ar(BitNot.ar(BitVal.ar(2r0)), Impulse.ar(0))}.plot(0.01)
// bit: 1111111111111111
{BitPrint.ar(BitAnd.ar(BitVal.ar(2r0110), BitVal.ar(2r1010)), Impulse.ar(0))}.plot(0.1)
// bit: 0000000000000010
{BitPrint.ar(BitOr.ar(BitVal.ar(2r0110), BitVal.ar(2r1010)), Impulse.ar(0))}.plot(0.1)
// bit: 0000000000001110
{BitPrint.ar(BitXor.ar(BitVal.ar(2r0110), BitVal.ar(2r1010)), Impulse.ar(0))}.plot(0.1)
// bit: 0000000000001100
{BitPrint.ar(BitSort.ar(BitVal.ar(2r0110)), Impulse.ar(0))}.plot(0.01)
// bit: 0000000000000011


{BitPrint.kr(BitNot.kr(BitVal.kr(2r0)), Impulse.kr(0))}.plot(0.01)
// bit: 1111111111111111
{BitPrint.kr(BitAnd.kr(BitVal.kr(2r0110), BitVal.kr(2r1010)), Impulse.kr(0))}.plot(0.1)
// bit: 0000000000000010
{BitPrint.kr(BitOr.kr(BitVal.kr(2r0110), BitVal.kr(2r1010)), Impulse.kr(0))}.plot(0.1)
// bit: 0000000000001110
{BitPrint.kr(BitXor.kr(BitVal.kr(2r0110), BitVal.kr(2r1010)), Impulse.kr(0))}.plot(0.1)
// bit: 0000000000001100
{BitPrint.kr(BitSort.kr(BitVal.kr(2r0110)), Impulse.kr(0))}.plot(0.01)
// bit: 0000000000000011




{(BitAnd.ar(BitVal.ar(2r0110), BitVal.ar(2r1100)) - BitVal.ar(2r0100))}.plot(0.1)
{(BitOr.ar(BitVal.ar(2r0110), BitVal.ar(2r1100)) - BitVal.ar(2r1))}.plot(0.1)


{BitPrint.ar(BitAnd.ar(BitVal.ar(2r0110111), BitVal.ar(2r1011111)), Impulse.ar(0))}.plot(0.1)



{BitPrint.ar(BitVal.ir(2r11111), Impulse.ar(30)) * SinOsc.ar}.plot(0.1)



{BitVal.ar(2r0101010101010101)}.plot(0.01)


{BitPrint.ar(1000.2335, Impulse.ar(30))}.plot(0.1)


{var trig = Impulse.ar(30); BitPrint.ar(Demand.ar(trig, 0, DIBitVal(Dwhite(0, 2r11111111))), trig)}.plot(0.5)


rrand(0, 2r11111111)



Writing 