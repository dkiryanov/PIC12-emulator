#pragma once
#define PROG_MEM_SIZE		0x400
#define DATA_MEM_SIZE		0x0FF
#define UNREAl_OFFSET		0x80
#define STACK_SIZE			8

#define STATUS_C			0
#define STATUS_DC			1
#define STATUS_Z			2
#define STATUS_PD			3
#define STATUS_TO			4
#define STATUS_RP0			5

#define INTCON_GIE			7

#define TMR0				0x01
#define PCL					0x02
#define STATUS				0x03
#define FSR					0x04
#define GPIO				0x05
#define PCLATH				0x0A
#define INTCON				0x0B
#define PIR1				0x0C
#define TMR1L				0x0E
#define TMR1H				0x0F
#define T1CON				0x10
#define CMCON				0x19
#define OPTION_REG			0x81
#define TRISIO				0x85
#define PIE1				0x8C
#define PCON				0x8E
#define OSCCAL				0x90
#define WPU					0x95
#define IOC					0x96
#define VRCON				0x99
#define EEDATA				0x9A
#define EEADR				0x9B
#define EECON1				0x9C

class Pic12Processor
{
	public:
		Pic12Processor();
		~Pic12Processor();

		unsigned char W;						// Accumulator
		int PC;									// Program counter
		unsigned int WDT;						// Watchdog timer
		short prog[PROG_MEM_SIZE];				// Program memory
		unsigned char real_mem[DATA_MEM_SIZE];
		unsigned char *mem[DATA_MEM_SIZE];		// Data memory
		int STACK[STACK_SIZE];					// Call stack
		unsigned char stack_ptr;
};