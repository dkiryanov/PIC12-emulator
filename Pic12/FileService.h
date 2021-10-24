#pragma once
#include <string>
class Processor;

class FileService
{
	public:
		FileService();
		~FileService();

		static int LoadFromHexFile(const char *file_name, Processor& processor);
	int SaveProgramMemory(Processor processor) const;
	template <class T>
	static std::string ConvertIntToHex(T i);

private:
		const std::string PROGRAM_MEMORY_FILE_NAME = "program_memory.txt";

		static unsigned char GetByte(FILE *file);
		static char ConvertAsciiToDecimal(char x);
};

