#pragma once

#define GetSevenBitsValue(x)	((x) & 0x07F)
#define GetEightBitsValue(x)	((x) & 0x0FF)
#define GetElevenBitsValue(x)	((x) & 0x7FF)
#define GetThreeBitsValue(x)	(((x) >> 7) & 7)
#define GetBit(x, y)		(((x) >> (y)) & 1)
#define SetBit(x, y)		((x) |= (1 << (y)))
#define ClearBit(x, y)		((x) &= ~(1 << (y)))

#define Registers(x, y)		(*x[(GetBit(*DataMemory[STATUS], STATUS_RP0) ? y + OFFSET : y)])

class Macroces
{
	public:
		Macroces();
		~Macroces();
};