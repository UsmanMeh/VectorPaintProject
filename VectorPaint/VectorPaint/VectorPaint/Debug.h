#pragma once
#include <iostream>
class Debug
{
	static std::string mConsoleString;
public:

	static void Initialize();
	static void RenderGUI();
	static void Clean();
	static void LogToConsole(std::string pLogString , bool LogToCmd = false);
	static void Log(std::string pLogString);
};

