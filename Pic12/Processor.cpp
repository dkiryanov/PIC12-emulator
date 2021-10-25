#include "stdafx.h"
#include "Processor.h"
#include "RegisterConstants.h"
#include "Macroces.h"
#include <cassert>
#include <cmath>
#include <iostream>


Processor::Processor()
{
	for (int i = 0; i < DATA_MEMORY_SIZE; i++)
	{
		DataMemory[i] = &SavedDataMemory[i];
		SavedDataMemory[i] = 0;
	}

	for (int i = 0; i < PROGRAM_MEMORY_SIZE; i++)
	{
		ProgramMemory[i] = 0;
	}

	DataMemory[OFFSET + PCL] = DataMemory[PCL];
	DataMemory[OFFSET + STATUS] = DataMemory[STATUS];
	DataMemory[OFFSET + FSR] = DataMemory[FSR];
	DataMemory[OFFSET + PCLATH] = DataMemory[PCLATH];
	DataMemory[OFFSET + INTCON] = DataMemory[INTCON];

	SetBit(*DataMemory[STATUS], STATUS_PD);
	SetBit(*DataMemory[STATUS], STATUS_TO);

	PC = 0;
	W = 0;
	WDT = 0;
	CallStackPointer = -1;
}

Processor::~Processor()
{
}

short Processor::GetCurrentData()
{
	return ProgramMemory[PC];
}

void Processor::ADDWF(unsigned char d, unsigned char f)
{
	printf("ADDWF 0x%02X, %d", f, d);

	unsigned char fRegisterValue = Registers(DataMemory, f);
	unsigned char result = W + fRegisterValue;

	bool shouldSetStatusC = static_cast<int>(fRegisterValue & 0xff) + (W & DATA_MEMORY_SIZE) > DATA_MEMORY_SIZE;
	
	if (shouldSetStatusC)
	{
		SetBit(*DataMemory[STATUS], STATUS_C);
	}
	else
	{
		ClearBit(*DataMemory[STATUS], STATUS_C);
	}

	bool shouldSetStatusDc = static_cast<int>(fRegisterValue & 0x0f) + (W & 0x0f) > 0x0f;

	if (shouldSetStatusDc)
	{
		SetBit(*DataMemory[STATUS], STATUS_DC);
	}
	else
	{
		ClearBit(*DataMemory[STATUS], STATUS_DC);
	}

	if (!(d & 0x1)) 
	{
		W = result;
	}
	else
	{
		ResetPrescaler(f);

		Registers(DataMemory, f) = result;
	}

	SetZeroFlag(result);
	PC++;
}

void Processor::ANDWF(unsigned char d, unsigned char f)
{
	printf("ANDWF 0x%02X, %d", f, d);

	unsigned char fRegisterValue = Registers(DataMemory, f);
	unsigned char result = W & fRegisterValue;

	if (!(d & 0x1))
	{
		W = result;
	}
	else 
	{
		Registers(DataMemory, f) = result;

		ResetPrescaler(f);
	}

	SetZeroFlag(result);
	PC++;
}

void Processor::CLRF(unsigned char d, unsigned char f)
{
	printf("CLRF 0x%02X", f);

	Registers(DataMemory, f) = 0;

	SetBit(*DataMemory[STATUS], STATUS_Z);

	PC++;
}

void Processor::CLRW()
{
	printf("CLRW");

	W = 0;

	SetBit(*DataMemory[STATUS], STATUS_Z);

	PC++;
}

void Processor::COMF(unsigned char d, unsigned char f)
{
	printf("COMF 0x%02X, %d", f, d);

	char result = ~Registers(DataMemory, f);

	result ? ClearBit(*DataMemory[STATUS], STATUS_Z) : SetBit(*DataMemory[STATUS], STATUS_Z);
		
	(d ? Registers(DataMemory, f) : W) = result;

	PC++;
}

void Processor::DECF(unsigned char d, unsigned char f)
{
	printf("DECF 0x%02X, %d", f, d);

	unsigned char result = Registers(DataMemory, f);;

	result == 0x00 ? result = 0xff : result--;

	if (d == 0)
	{
		W = result;
	}
	else 
	{
		Registers(DataMemory, f) = result;

		ResetPrescaler(f);
	}

	SetZeroFlag(result);
	PC++;

}

void Processor::DECFSZ(unsigned char d, unsigned char f)
{
	printf("DECFSZ 0x%02X, %d", f, d);

	unsigned char result = Registers(DataMemory, f);
	
	assert(d == 0 || d == 1);

	result == 0x00 ? result = 0xff : result--;

	if (d == 0)
	{
		W = result;
	}
	else 
	{
		Registers(DataMemory, f) = result;

		ResetPrescaler(f);
	}

	result == 0 ? PC = PC + 2 : PC++;
}

void Processor::INCF(unsigned char d, unsigned char f)
{
	printf("INCF 0x%02X, %d", f, d);

	unsigned char result = Registers(DataMemory, f);

	result++;

	if (d == 0)
	{
		W = result;
	}
	else 
	{
		Registers(DataMemory, f) = result;

		ResetPrescaler(f);
	}

	SetZeroFlag(result);
	PC++;
}

void Processor::INCFSZ(unsigned char d, unsigned char f)
{
	printf("INCFSZ 0x%02X, %d", f, d);

	unsigned char result = Registers(DataMemory, f);

	result++;

	if (d == 0)
	{
		W = result;
	}
	else 
	{
		Registers(DataMemory, f) = result;

		ResetPrescaler(f);
	}

	result == 0 ? PC += 2 : PC++;
}

void Processor::IORWF(unsigned char d, unsigned char f)
{
	printf("IORWF 0x%02X, %d", f, d);

	unsigned char fRegisterValue = Registers(DataMemory, f);

	assert(d == 0 || d == 1);

	unsigned char result = (W | fRegisterValue) & 0x7f;

	if (d & 0x1) 
	{
		Registers(DataMemory, f) = result;

		ResetPrescaler(f);
	}
	else 
	{
		W = result;
	}

	SetZeroFlag(result);
	PC++;
}

void Processor::MOVF(unsigned char d, unsigned char f)
{
	printf("MOVF 0x%02X, %d", f, d);

	unsigned char result = Registers(DataMemory, f);

	if (d) // Если d=1, значение сохраняется в регистре 'f'
	{
		Registers(DataMemory, f) = result;

		ResetPrescaler(f);
	}
	else
	{
		// Если d=0, значение сохраняется в регистре W
		W = result;
	}

	// Изменяем флаг Z
	SetZeroFlag(result);

	// Увеличиваем счетчик команд
	PC++;
}

void Processor::MOVWF(unsigned char d, unsigned char f)
{
	printf("MOVWF 0x%02X", f);

	Registers(DataMemory, f) = W;

	PC++;
}

void Processor::NOP()
{
	printf("NOP");

	PC++;
}

void Processor::RLF(unsigned char d, unsigned char f)
{
	printf("RLF 0x%02X, %d", f, d);

	unsigned char result = Registers(DataMemory, f);

	unsigned char newBitC = GetBit(*DataMemory[STATUS], STATUS_C);

	unsigned char oldBitC = newBitC;

	newBitC = (result & 128) >> 7;
	result = result << 1 | oldBitC;

	if (d == 0)
	{
		W = result;
	}
	else 
	{
		Registers(DataMemory, f) = result;

		ResetPrescaler(f);
	}

	newBitC ? SetBit(*DataMemory[STATUS], STATUS_C) : ClearBit(*DataMemory[STATUS], STATUS_C);

	PC++;
}

void Processor::RRF(unsigned char d, unsigned char f)
{
	printf("RRF 0x%02X, %d", f, d);

	unsigned char result = Registers(DataMemory, f);

	unsigned char newBitC = GetBit(*DataMemory[STATUS], STATUS_C);

	unsigned char oldBitC = newBitC;

	newBitC = result & 1;
	result = result >> 1 | oldBitC << 7;

	if (d == 0)
	{
		W = result;
	}
	else 
	{
		Registers(DataMemory, f) = result;

		ResetPrescaler(f);
	}

	newBitC ? SetBit(*DataMemory[STATUS], STATUS_C) : ClearBit(*DataMemory[STATUS], STATUS_C);

	PC++;
}

void Processor::SUBWF(unsigned char d, unsigned char f)
{
	printf("SUBWF 0x%02X, %d", f, d);

	unsigned char fRegisterValue = Registers(DataMemory, f);
	unsigned char result = fRegisterValue - W;

	if (d & 0x1) 
	{
		Registers(DataMemory, f) = result;

		ResetPrescaler(f);
	}
	else
	{
		W = result;
	}

	unsigned char flagZ = static_cast<int>(fRegisterValue) - W == 0 ? 1 : 0;
	flagZ ? SetBit(*DataMemory[STATUS], STATUS_Z) : ClearBit(*DataMemory[STATUS], STATUS_Z);

	unsigned char flagC = static_cast<int>(fRegisterValue & 0xff) - (W & 0xff)	< 0 ? 0 : 1;
	flagC ? SetBit(*DataMemory[STATUS], STATUS_C) : ClearBit(*DataMemory[STATUS], STATUS_C);

	unsigned char flagDC = static_cast<int>(fRegisterValue & 0x0f) - (W & 0x0f)	< 0 ? 0 : 1;
	flagDC ? SetBit(*DataMemory[STATUS], STATUS_DC) : ClearBit(*DataMemory[STATUS], STATUS_DC);

	PC++;
}

void Processor::SWAPF(unsigned char d, unsigned char f)
{
	printf("SWAPF 0x%02X, %d", f, d);

	unsigned char fRegisterValue = Registers(DataMemory, f);
	int binFRegisterValue = ConvertDecimalToBin(fRegisterValue);
	int joined = Join(binFRegisterValue % 10000, binFRegisterValue / 10000);

	unsigned char result = static_cast<unsigned char>(ConvertBinToDecimal(joined));

	if (d == 0)
	{
		W = result;
	}
	else 
	{
		Registers(DataMemory, f) = result;

		ResetPrescaler(f);
	}

	PC++;
}

void Processor::XORWF(unsigned char d, unsigned char f)
{
	printf("XORWF 0x%02X, %d", f, d);

	unsigned char result = W ^ Registers(DataMemory, f);

	if (d == 0)
	{
		W = result;
	}
	else
	{
		Registers(DataMemory, f) = result;

		ResetPrescaler(f);
	}

	SetZeroFlag(result);
	PC++;
}

void Processor::BCF(unsigned char b, unsigned char f)
{
	printf("BCF 0x%02X, %d", f, b);

	ClearBit(Registers(DataMemory, f), b);

	PC++;
}

void Processor::BSF(unsigned char b, unsigned char f)
{
	printf("BSF 0x%02X, %d", f, b);

	SetBit(Registers(DataMemory, f), b);

	PC++;
}

void Processor::BTFSC(unsigned char b, unsigned char f)
{
	printf("BTFSC 0x%02X, %d", f, b);

	if (*DataMemory[f] >> b & 1)
	{
		PC++;
	}
	else
	{
		PC++;
		NOP();
	}
}

void Processor::BTFSS(unsigned char b, unsigned char f)
{
	printf("BTFSS 0x%02X, %d", f, b);

	if (*DataMemory[f] >> b & 1)
	{
		PC++;
		NOP();
	}
	else
	{
		PC++;
	}
}

void Processor::ADDLW(unsigned char k)
{
	printf("ADDLW 0x%02X", k);

	255 - W < k ? SetBit(*DataMemory[STATUS], STATUS_C) : ClearBit(*DataMemory[STATUS], STATUS_C);

	255 - static_cast<unsigned char>(W << 4) < static_cast<unsigned char>(k << 4) ? 
		SetBit(*DataMemory[STATUS], STATUS_DC) : 
	ClearBit(*DataMemory[STATUS], STATUS_DC);

	W += k;

	W == 0 ? SetBit(*DataMemory[STATUS], STATUS_Z) : ClearBit(*DataMemory[STATUS], STATUS_Z);

	PC++;
}

void Processor::ANDLW(unsigned char k)
{
	printf("ANDLW 0x%02X", k);

	unsigned char result = W & k;

	W = result;

	SetZeroFlag(result);

	PC++;
}

void Processor::GOTO(short k)
{
	printf("GOTO 0x%02X", k);

	assert( k >= 0 && k <= 2047);

	int pclath = Registers(DataMemory, PCLATH);

	PC = k | (pclath >> 3 & 3) << 11;
}

void Processor::CALL(short k)
{
	printf("CALL 0x%02X", k);

	CallStackPush(PC + 1);

	GOTO(k);
}

void Processor::CLRWDT()
{
	printf("CLRWDT");

	WDT = 0;

	SetBit(*DataMemory[STATUS], STATUS_TO);
	SetBit(*DataMemory[STATUS], STATUS_PD);

	SetBit(*DataMemory[OPTION_REG], 0);
	SetBit(*DataMemory[OPTION_REG], 1);
	SetBit(*DataMemory[OPTION_REG], 2);
}

void Processor::IORLW(unsigned char k)
{
	printf("IORLW 0x%02X", k);

	W = W | k;

	W == 0 ? SetBit(*DataMemory[STATUS], STATUS_Z) : ClearBit(*DataMemory[STATUS], STATUS_Z);

	PC++;
}

void Processor::MOVLW(unsigned char k)
{
	printf("MOVLW 0x%02X", k);

	W = k;

	PC++;
}

void Processor::RETFIE()
{
	printf("RETFIE");

	PC = CallStackPop();

	SetBit(*DataMemory[INTCON], INTCON_GIE);
}

void Processor::RETLW(unsigned char k)
{
	printf("RETLW 0x%02X", k);

	PC = CallStackPop();

	W = k;
}

void Processor::RETURN()
{
	printf("RETURN");

	PC = CallStackPop();
}

void Processor::SLEEP()
{
	printf("SLEEP");

	WDT = 0;

	SetBit(*DataMemory[STATUS], STATUS_TO);
	ClearBit(*DataMemory[STATUS], STATUS_PD);

	SetBit(*DataMemory[OPTION_REG], 0);
	SetBit(*DataMemory[OPTION_REG], 1);
	SetBit(*DataMemory[OPTION_REG], 2);
	
	printf("Controller is in the sleep mode...");
}

void Processor::SUBLW(unsigned char k)
{
	printf("SUBLW 0x%02X", k);

	unsigned char flagZ = static_cast<int>(k) - W == 0 ? 1 : 0;
	flagZ ? SetBit(*DataMemory[STATUS], STATUS_Z) : ClearBit(*DataMemory[STATUS], STATUS_Z);

	unsigned char flagC = static_cast<int>(k & 0xff) - (W & 0xff)	< 0 ? 0 : 1;
	flagC ? SetBit(*DataMemory[STATUS], STATUS_C) : ClearBit(*DataMemory[STATUS], STATUS_C);

	unsigned char flagDC = static_cast<int>(k & 0x0f) - (W & 0x0f)	< 0 ? 0 : 1;
	flagDC ? SetBit(*DataMemory[STATUS], STATUS_DC) : ClearBit(*DataMemory[STATUS], STATUS_DC);

	W = k - W;
	PC++;
}

void Processor::XORLW(unsigned char k)
{
	printf("XORLW 0x%02X", k);

	W ^= k;
	W ? ClearBit(*DataMemory[STATUS], STATUS_Z) : SetBit(*DataMemory[STATUS], STATUS_Z);

	PC++;
}

/*********************** 
 *** PRIVATE MEMBERS ***
 ***********************/

void Processor::SetZeroFlag(unsigned char result)
{
	result == 0 ? SetBit(*DataMemory[STATUS], STATUS_Z) : ClearBit(*DataMemory[STATUS], STATUS_Z);
}

void Processor::CallStackPush(int pcToAdd)
{
	CallStack[CallStackPointer] = pcToAdd & 0x1FFF;

	CallStackPointer++;
}

int Processor::CallStackPop()
{
	int newPC = CallStack[CallStackPointer];

	assert(CallStackPointer>0 && CallStackPointer <= STACK_SIZE);

	CallStack[CallStackPointer] = 0;
	CallStackPointer--;

	return newPC;
}

int Processor::Join(int a, int b)
{
	return a * 10000 + b;
}

int Processor::ConvertBinToDecimal(int a) const
{
	int b = a;
	int ret = 0;

	for (int i = 0; i <= 7; i++)
	{
		ret = ret + b % 10 * pow(2, i);
		b = (b - b % 10) / 10;
	}

	return ret;
}

int Processor::ConvertDecimalToBin(int value) const
{
	int result = 0;
	int Count_D = value;

	for (int i = 0; i <= 7; i++)
	{
		result = result + Count_D % 2 * pow(10, i);

		Count_D = Count_D / 2;
	}

	return result;
}

void Processor::ResetPrescaler(unsigned char f)
{
	if (f == TMR0 && GetBit(*DataMemory[OPTION_REG], 3) == 0)
	{
		SetBit(*DataMemory[OPTION_REG], 0);
		SetBit(*DataMemory[OPTION_REG], 1);
		SetBit(*DataMemory[OPTION_REG], 2);
	}
}
