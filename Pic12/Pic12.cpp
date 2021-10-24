// Pic12.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <assert.h>
#include <stdio.h>
#include <string>
#include "ChangeAnalizer.h"
#include "Interpretator.h"
#include "FileService.h"
#include <iostream>

using namespace std;

const int DEBUG_MODE = 1;

int main(int argc, char **argv)
{
	cout << "PIC12 Emulator" << endl;
	cout << "1: DEBUG mode" << endl;
	std:cout << "2: NON-DEBUG mode" << endl;

	int mode;
	cin >> mode;

	mode == DEBUG_MODE ? 
		cout << "you have chosen the DEBUG mode..." << endl : 
	cout << "you have cosen NON-DEBUG mode" << endl;

	Processor processor;
	FileService fileService;

	string fileName;
	cout << "type the path to your .hex file: ";
	cin >> fileName;
	cout << endl;

	fileService.LoadFromHexFile(fileName.c_str(), processor);

	cout << "data has been loaded successfully..." << endl;

	Interpretator interpretator;
	ChangeAnalizer analyzer;

	cout << "Starting PIC12 emulation..." << endl << endl;

	while (true)
	{
		Processor previous = processor;
		interpretator.Interpret(processor);

		if (mode == DEBUG_MODE)
		{
			getchar();
		}
		
		analyzer.AnalyzeChanges(previous, processor);
		fileService.SaveProgramMemory(processor);
	}
}