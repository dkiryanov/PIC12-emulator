#pragma once
#include "Pic12Processor.h"

class Pic12Commands
{
	public:
		Pic12Commands();
		~Pic12Commands();
		
		void CLRW(Pic12Processor& processor);
};

