#include "stdafx.h"
#include "Console.h"
#include <cstdlib>
#include <cstring>
#include <fstream>


namespace se
{
	Console g_Console;

	Console::Console()
	{


	}


	Console::~Console()
	{
	}
	void Console::fetchInput()
	{

		while (g_RenderManager.GetRenderWindow()->isOpen())
		{
			std::string input;


			std::getline(std::cin, input);

			g_Console.runCommand(input);
		}
	}
	void Console::setup()
	{
		fetchThread = new std::thread(&Console::fetchInput, g_Console);

		fetchThread->detach();
	}
	void Console::runCommand(std::string command)
	{

		//THIS SH*T WILL BE BROKEN OUT INTO LUA.



		std::string c = command.substr(0, command.find(' '));
		std::transform(c.begin(), c.end(), c.begin(), ::tolower);

		std::string p = command.substr(command.find(' ') + 1);

		

		if (c == "reload")
		{
			if (p == "locals" || p == "local" || p == "lang")
				g_Localization.reload();
			else if (p == "content")
				se::Content::reload();
			else if (p == "config")
				se::Config::reload();
			else
				se::Tools::Print("Reload type '" + p + "' not found.");
				
		}
		else
		{
			se::Tools::Print("Command not found.");
		}

	}
}
