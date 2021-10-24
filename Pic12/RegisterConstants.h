#pragma once

const int STATUS_C = 0;
const int STATUS_DC = 1;
const int STATUS_Z = 2;
const int STATUS_PD = 3;
const int STATUS_TO = 4;
const int STATUS_RP0 = 5;

const int INTCON_GIE = 7;

const int TMR0 = 0x01;
const int PCL = 0x02;
const int STATUS = 0x03;
const int FSR = 0x04;
const int GPIO = 0x05;
const int PCLATH = 0x0A;
const int INTCON = 0x0B;
const int PIR1 = 0x0C;
const int TMR1L = 0x0E;
const int TMR1H = 0x0F;
const int T1CON = 0x10;
const int CMCON = 0x19;
const int OPTION_REG = 0x81;
const int TRISIO = 0x85;

const int PCON = 0x8E;
const int OSCCAL = 0x90;
const int WPU = 0x95;
const int IOC = 0x96;
const int VRCON = 0x99;
const int EEDATA = 0x9A;
const int EEADR = 0x9B;
const int EECON1 = 0x9C;
const int PIE1 = 0x8C;

class RegisterConstants
{
	public:
		RegisterConstants();
		~RegisterConstants();
};