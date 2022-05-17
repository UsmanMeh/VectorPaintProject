#pragma once
#include <iostream>
class Debug
{
	std::string mConsoleString;
public:
	static Debug* instance;
	static Debug* GetInstance();

	void Initialize();
	void RenderGUI();
	void Clean();
	void Log(std::string);
};

