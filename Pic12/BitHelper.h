#pragma once

#define BIT_GET(x, y)		(((x) >> (y)) & 1)
#define BIT_SET(x, y)		((x) |= (1 << (y)))
#define BIT_CLEAR(x, y)		((x) &= ~(1 << (y)))

class BitHelper
{
	public:
		BitHelper();
		~BitHelper();
};