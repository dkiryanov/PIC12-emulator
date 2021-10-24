#include "stdafx.h"
#include "FileService.h"
#include "Processor.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <bitset>


FileService::FileService()
{
}


FileService::~FileService()
{
}

int FileService::LoadFromHexFile(const char *file_name, Processor& processor)
{
	FILE *file = fopen(file_name, "r");

	if (!file)
	{
		return 1;
	}

	unsigned char temp[260];

	while (true)
	{
		int symbol = fgetc(file);

		if (symbol == EOF)
		{
			fclose(file);
			return 0;
		}

		if (symbol == '\r' || symbol == '\n')
		{
			continue;
		}

		if (symbol != ':')
		{
			fclose(file);
			return 2;
		}

		temp[0] = GetByte(file);
		temp[1] = GetByte(file);
		temp[2] = GetByte(file);
		temp[3] = GetByte(file);

		for (int i = 0; i <= temp[0]; i++)
		{
			temp[4 + i] = GetByte(file);
		}

		unsigned offset;
		
		switch (temp[3])
		{
			case 0:				
				offset = (temp[1] << 8) | temp[2];

				if (offset >= PROGRAM_MEMORY_SIZE)
				{
					break;
				}

				for (int i = 0; i < temp[0]; i += 2)
				{
					processor.ProgramMemory[offset++] = temp[i + 5] << 8 | temp[i + 4];
				}

				return 0;
			case 1:								
				return 0;
			default: break;
		}
	}
}

int FileService::SaveProgramMemory(Processor processor) const
{
	std::ofstream programMemoryFile(PROGRAM_MEMORY_FILE_NAME);
	
	programMemoryFile.clear();

	if (programMemoryFile.is_open())
	{
		for (int i = 0; i < PROGRAM_MEMORY_SIZE; i++) 
		{
			programMemoryFile 
				<< "0x" << std::hex << std::setfill('0') << std::setw(2) << i << " "
				<< std::bitset<8>(processor.ProgramMemory[i]) << " "
				<< std::bitset<16>(processor.ProgramMemory[i])
				<< std::endl;
		}

		programMemoryFile.close();
	}

	else std::cout << "Unable to open file";

	return 0;
}

char FileService::ConvertAsciiToDecimal(char x)
{
	if (x >= '0' && x <= '9')
	{
		return x - 48;
	}

	if (x >= 'A' && x <= 'F')
	{
		return x - 55;
	}

	return 0;
}

unsigned char FileService::GetByte(FILE *file)
{
	return ConvertAsciiToDecimal(fgetc(file)) << 4 | ConvertAsciiToDecimal(fgetc(file));
}
