// Pic12.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <assert.h>
#include <stdio.h>
#include <string>
#include "ChangeAnalizer.h"
#include "Interpretator.h"
#include "FileService.h"

using namespace std;

int main(int argc, char **argv)
{
	Processor processor;
	FileService fileService;

	fileService.LoadFromHexFile("loop.hex", processor);

	Interpretator interpretator;
	ChangeAnalizer analyzer;

	while (true)
	{
		Processor previous = processor;
		interpretator.Interpret(processor);
		getchar();
		analyzer.AnalyzeChanges(previous, processor);
		fileService.SaveProgramMemory(processor);
	}
}