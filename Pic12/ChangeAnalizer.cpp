#include "stdafx.h"
#include "ChangeAnalizer.h"
#include "Processor.h"
#include "RegisterConstants.h"
#include <iostream>


ChangeAnalizer::ChangeAnalizer()
{
}

ChangeAnalizer::~ChangeAnalizer()
{
}

void ChangeAnalizer::AnalyzeChanges(Processor previous, Processor current)
{
	if (current.W != previous.W) // сравниваем текущее состояние W с предыдущим
	{
		printf("\tW = %d\n", current.W);
	}

	for (int i = 0; i < DATA_MEMORY_SIZE; i++)
	{
		if (current.SavedDataMemory[i] == previous.SavedDataMemory[i])
		{
			continue;
		}
		// получаем данные из памяти данных
		char data = current.SavedDataMemory[i];

		switch (i) // выводим информацию об изменении регистра STATUS
		{
			case STATUS:
				std::cout << "STATUS = ";
				break;
			case STATUS + OFFSET:
				continue;
			default:
				printf("\t%02Xh = ", i);
		}
		// выводим информацию об измененных данных
		for (int j = 0; j < 8; j++)
		{
			if (data & 0x80)
			{
				printf("1");
			}
			else
			{
				printf("0");
			}

			data <<= 1;
		}

		std::cout << std::endl;
	}
}