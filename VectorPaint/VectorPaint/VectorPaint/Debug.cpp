#include "Debug.h"
#include <imgui.h>
std::string Debug::mConsoleString = "";
void Debug::Initialize()
{

}
void Debug::RenderGUI()
{
	bool open;
	ImGui::Begin("Debug Window",&open, ImGuiWindowFlags_AlwaysVerticalScrollbar);
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
void Debug::LogToConsole(std::string pLogString , bool LogToCmd )
{
	mConsoleString += "\n";
	mConsoleString += pLogString;
	Log(pLogString);
}
void Debug::Log(std::string pLogString)
{
	std::cout << pLogString << std::endl;
}
