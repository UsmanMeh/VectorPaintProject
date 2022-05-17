#include "Debug.h"
#include <imgui.h>
Debug* Debug::instance = nullptr;
Debug* Debug::GetInstance()
{
	if (!instance)
	{
		instance = new Debug;
	}
	return instance;
}
void Debug::Initialize()
{

}
void Debug::RenderGUI()
{
	ImGui::Begin("Debug Window");
	if (ImGui::Button("Clear"))
	{
		mConsoleString.clear();
	}
	ImGui::TextWrapped(mConsoleString.c_str());
	ImGui::End();
}
void Debug::Clean()
{

}
void Debug::Log(std::string pLogString)
{
	mConsoleString += "\n";
	mConsoleString += pLogString;
}
