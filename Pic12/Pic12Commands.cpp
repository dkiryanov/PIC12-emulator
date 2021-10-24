#include "stdafx.h"
#include "Pic12Commands.h"
#include "BitHelper.h"


Pic12Commands::Pic12Commands()
{
}

Pic12Commands::~Pic12Commands()
{
}

void Pic12Commands::CLRW(Pic12Processor& processor)
{
	printf("CLRW");

	processor.W = 0;
	auto bitToChange = processor.mem[STATUS];
	unsigned char c = 0;
	BIT_SET(bitToChange, c);
	processor.PC++;
}