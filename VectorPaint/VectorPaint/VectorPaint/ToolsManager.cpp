#include "ToolsManager.h"


ToolsManager* ToolsManager::instance = nullptr;
ToolsManager* ToolsManager::GetInstance()
{
	if (!instance)
	{
		instance = new ToolsManager;
		instance->Initialize();
	}
	return instance;
}
void ToolsManager::Initialize()
{
	for (int tool = 0; tool < Tools::size; tool++)
	{
		ToolsList.insert(std::pair<Tools, bool>(static_cast<Tools>(tool), false));
	}
	ToolsList[Tools::Square] = true;
	//Selection , Line, Square, Rectangle, Triangle, Circle , size
	ToolsNameList.insert(std::pair<Tools, std::string>(Tools::Selection,"[NA]Selection Tool"));
	ToolsNameList.insert(std::pair<Tools, std::string>(Tools::Line,"[NA]Line Tool"));
	ToolsNameList.insert(std::pair<Tools, std::string>(Tools::Square,"Square Tool"));
	ToolsNameList.insert(std::pair<Tools, std::string>(Tools::Rectangle,"Rectangle Tool"));
	ToolsNameList.insert(std::pair<Tools, std::string>(Tools::Triangle,"Triangle Tool"));
	ToolsNameList.insert(std::pair<Tools, std::string>(Tools::Circle,"[NA]Circle Tool"));
}
ToolsManager::Tools ToolsManager::GetSelectedTool()
{
		return SelectedTool;
}

void ToolsManager::SetSelectedTool(Tools pSelectedTool)
{
	SelectedTool = pSelectedTool;
}
glm::vec4 ToolsManager::GetCurrentColor()
{
	return mColor;
}
void ToolsManager::SetCurrentColor(glm::vec4 pColor)
{
	mColor = pColor;
}