#pragma once

const int PROGRAM_MEMORY_SIZE = 1024;
const int DATA_MEMORY_SIZE = 255;
const int OFFSET = 128;
const int STACK_SIZE = 8;

/*
 * PIC12F6XX emulator
 * 
 * Эмулятор PIC12F6XX
*/
class Processor
{
	public:

		/*
		 * Accumulator
		 * Рабочий регистр (аккумулятор)
		 */
		unsigned char W;	
	
		/*
		 * Program counter
		 * Счетчик команд
		 */
		int PC;									
		
		/*
		 * Watchdog timer
		 * Сторожевой таймер WDT
		 */
		unsigned int WDT;		
	
		short ProgramMemory[PROGRAM_MEMORY_SIZE];

		unsigned char SavedDataMemory[DATA_MEMORY_SIZE];

		unsigned char *DataMemory[DATA_MEMORY_SIZE];

		int CallStack[STACK_SIZE];

		unsigned char CallStackPointer;

		Processor();
		~Processor();

		short GetCurrentData();
		
		/*
		 * Adds registers W and 'f'
		 *
		 * Сложить содержимое регистров W и 'f'. 
		 * Если d=0, результат сохраняется в регистре W. 
		 * Если d=1, результат сохраняется в регистре 'f'.
		 */
		void ADDWF(unsigned char d, unsigned char f);

		/*
		 * Performs the bitwise 'AND' of the W and 'f' registers. 
		 *
		 * Выполняется побитное 'И' содержимого регистров W и 'f'. 
		 * Если d=0, результат сохраняется в регистре W. 
		 * Если d=1, результат сохраняется в регистре 'f'.
		 */
		void ANDWF(unsigned char d, unsigned char f);

		/*
		 * Clear register 'f' and set Z flag
		 * Очистить содержимое регистра 'f' и установить флаг Z
		 */
		void CLRF(unsigned char d, unsigned char f);

		/*
		 * Clear register W and set Z flag
		 * Очистить содержимое регистра W и установить флаг Z 
		 */
		void CLRW();

		/*
		 * Inverts all bits in the 'f' register
		 * 
		 * Инвертировать все биты в регистре 'f'. 
		 * Если d=0, результат сохраняется в регистре W. 
		 * Если d=1, результат сохраняется в регистре 'f'.
		 */
		void COMF(unsigned char d, unsigned char f);

		/*
		 * Decrements the 'f' register
		 * 
		 * Декрементировать содержимое регистра 'f'. 
		 * Если d=0, результат сохраняется в регистре W. 
		 * Если d=1, результат сохраняется в регистре 'f'.
		 */
		void DECF(unsigned char d, unsigned char f);

		/*
		 * Decrements 'f' register
		 * 
		 * Декрементировать содержимое регистра 'f'. 
		 * Если d=0, результатсохраняетсяврегистре W. 
		 * Если d=1, результатсохраняетсяврегистре 'f'. 
		 * Еслирезультат не равен '0' , то исполняется следующая инструкция. 
		 */
		void DECFSZ(unsigned char d, unsigned char f);

		/*
		 * Adds 1 to f register
		 * 
		 * Инкрементировать содержимое регистра 'f'. 
		 * Если d=0, результат сохраняется в регистре W. 
		 * Если d=1, результат сохраняется в регистре 'f'.
		 */
		void INCF(unsigned char d, unsigned char f);

		/*
		 * Adds 1 to 'f' and skip if 0
		 * 
		 * Прибавить 1 к f и пропустить, если 0 
		 */
		void INCFSZ(unsigned char d, unsigned char f);

		/*
		 * Calculates bitwise 'OR' between W and 'f'
		 * 
		 * Побитное 'ИЛИ' W и f
		 */
		void IORWF(unsigned char d, unsigned char f);

		/*
		 * Sends 'f' value to the 'd' register
		 * Содержимое регистра 'f' пересылается в регистр адресата. 
		 */
		void MOVF(unsigned char d, unsigned char f);

		/*
		 * Sends contents of the W register to the 'f' register
		 * 
		 * Переслать содержимое регистра W в регистр 'f'.
		 */
		void MOVWF(unsigned char d, unsigned char f);

		/*
		 * No operation to perform
		 * Нет операции
		 */
		void NOP();

		/*
		 * Cyclic left shift of the contents of the 'f' register through the C bit of the STATUS register. 
		 * 
		 * Выполняется циклический сдвиг влево содержимого регистра 'f' 
		 * через бит C регистра STATUS. Если d=0, результат сохраняется в регистре W. 
		 * Если d=1, результат сохраняется в регистре 'f'.
		 */
		void RLF(unsigned char d, unsigned char f);

		/*
		 * Cyclic right shift of the contents of the 'f' register is performed 
		 * through the C bit of the STATUS register. 
		 * 
		 * Выполняется циклический сдвиг вправо содержимого регистра 'f' 
		 * через бит C регистра STATUS. Если d=0, результат сохраняется врегистре W. 
		 * Если d=1, результат сохраняется в регистре 'f'. 
		 */
		void RRF(unsigned char d, unsigned char f);

		/*
		 * Substracts W value from the 'f' register
		 * 
		 * Вычесть содержимое регистра W из регистра 'f'. 
		 * Если d=0, результат сохраняется в регистре W. 
		 * Если d=1, результат сохраняется в регистре 'f'.
		 */
		void SUBWF(unsigned char d, unsigned char f);

		/*
		 * Swaps the high and low nibbles of the 'f' register.
		 * 
		 * Поменять местами старший и младший полубайты регистра 'f'. 
		 * Если d=0, результат сохраняется в регистре W. 
		 * Если d=1, результат сохраняется в регистре 'f'.
		 */
		void SWAPF(unsigned char d, unsigned char f);

		/*
		 * Calculates XOR between W and 'f' register
		 * 
		 * Побитное 'исключающее ИЛИ' W и f
		 */
		void XORWF(unsigned char d, unsigned char f);

		/*
		 * Clears bit 'b' in the 'f' register
		 * 
		 * Очистить бит b в регистре f 
		 */
		void BCF(unsigned char b, unsigned char f);

		/*
		 * Sets bit 'b' in the 'f' register
		 * 
		 * Установить бит b в регистре f
		 */
		void BSF(unsigned char b, unsigned char f);

		/*
		 * Check bit 'b' in the 'f' register and skip if 0
		 * 
		 * Проверить бит b в регистре f, пропустить если 0
		 */
		void BTFSC(unsigned char b, unsigned char f);

		/*
		 * Check bit 'b' in the 'f' register and skip if 1
		 * 
		 * Проверить бит b в регистре f, пропустить если 1 
		 */
		void BTFSS(unsigned char b, unsigned char f);

		/*
		 * Adds 'k' and W
		 * 
		 * Содержимое регистра W складывается с 8-разрядной константой 'k'. 
		 * Результат сохраняется в регистре W. 
		 */
		void ADDLW(unsigned char k);

		/*
		 * Performs biwise 'AND' of the constant 'k' and W register
		 * 
		 * Побитное 'И' константы и W
		 */
		void ANDLW(unsigned char k);

		/*
		 * Выполнить безусловный переход. 
		 * Одиннадцать бит адреса загружаются из кода команды в счетчик команд PC<10:0>. 
		 * Два старших бита загружаются в счетчик команд PC<12:11> из регистра PCLATH.
		 */
		void GOTO(short k);

		/*
		 * Вызов подпрограммы
		 */
		void CALL(short k);

		/*
		 * Resets WDT, sets bits TO and PD to STATUS
		 * 
		 * Сбрасывает WDT и предделитель, если он подключен к WDT. 
		 * В регистре STATUS устанавливает биты -TO и -PD. 
		 */
		void CLRWDT();

		/*
		 * Calculates bitwise OR between 'k' and W
		 * 
		 * Побитное 'ИЛИ' константыи W
		 */
		void IORLW(unsigned char k);

		/*
		 * Moves 'k' to the W register
		 * 
		 * Переслать константу 'k' в регистр W.
		 */
		void MOVLW(unsigned char k);

		/*
		 * Возврат из подпрограммы с разрешением прерываний
		 */
		void RETFIE();

		/*
		 * Возврат из подпрограммы с загрузкой константы в W
		 */
		void RETLW(unsigned char k);

		/*
		 * Возврат из подпрограммы
		 */
		void RETURN();

		/*
		 *  Sleep mode
		 */
		void SLEEP();

		/*
		 * Substracts W from 'k'
		 * Вычесть W из константы
		 */
		void SUBLW(unsigned char k);

		/*
		 * Bitwise XOR of 'k' and W
		 * 
		 * Побитное 'исключающее ИЛИ' константы и W
		 */
		void XORLW(unsigned char k);

	private:
		int ConvertDecimalToBin(int value) const;

		int ConvertBinToDecimal(int value) const;

		static int Join(int a, int b);

		void SetZeroFlag(unsigned char result);

		void CallStackPush(int pcToAdd);

		int CallStackPop();

		void ResetPrescaler(unsigned char f);
};