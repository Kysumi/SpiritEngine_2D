#pragma once
#include <thread>
#include <iostream>
namespace se
{
	class Console
	{
	public:
		Console();
		~Console();

		void fetchInput();
		void setup();

		std::thread* fetchThread;

		void runCommand(std::string command);
	};

	extern Console g_Console;
}
