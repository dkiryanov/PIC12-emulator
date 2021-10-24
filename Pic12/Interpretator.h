#pragma once
#include "Processor.h"

class Interpretator
{
	public:
		Interpretator();

		~Interpretator();

		static void Interpret(Processor& processor);
};