#pragma once
class Processor;

class ChangeAnalizer
{
	public:
		ChangeAnalizer();
		~ChangeAnalizer();

		static void AnalyzeChanges(Processor previous, Processor current);
};