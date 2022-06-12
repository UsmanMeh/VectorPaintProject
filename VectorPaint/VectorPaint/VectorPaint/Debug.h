#pragma once
#include <iostream>
#include <vector>
class Debug
{
private:
	static std::vector<std::string> mConsoleString;
public:
	static std::string TextureFilePath;
	static void Initialize();
	static void RenderGUI();
	static void Clean();
	//static void LogToConsole(bool pBoolVal);
	static void LogToConsole(std::string pLogString , bool LogToCmd = false);
	static void Log(std::string pLogString);
};

