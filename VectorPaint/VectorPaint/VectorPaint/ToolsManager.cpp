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
	SelectedTool = Rectangle;
	ToolsList[SelectedTool] = true;
	//Selection , Line, Square, Rectangle, Triangle, Circle ,Path , size
	ToolsNameList.insert(std::pair<Tools, std::string>(Tools::Selection,"Selection Tool"));
	ToolsNameList.insert(std::pair<Tools, std::string>(Tools::Line,"Line Tool"));
	ToolsNameList.insert(std::pair<Tools, std::string>(Tools::Square,"Square Tool"));
	ToolsNameList.insert(std::pair<Tools, std::string>(Tools::Rectangle,"Rectangle Tool"));
	ToolsNameList.insert(std::pair<Tools, std::string>(Tools::Triangle,"Triangle Tool"));
	ToolsNameList.insert(std::pair<Tools, std::string>(Tools::Circle,"Circle Tool"));
	ToolsNameList.insert(std::pair<Tools, std::string>(Tools::Path,"Path Tool"));
}
ToolsManager::Tools ToolsManager::GetSelectedTool()
{
		return SelectedTool;
}

void ToolsManager::SetSelectedTool(Tools pSelectedTool)
{
	ToolsList[SelectedTool] = false;
	SelectedTool = pSelectedTool;
	ToolsList[SelectedTool] = true;
}
glm::vec4 ToolsManager::GetCurrentColor()
{
	return mColor;
}
void ToolsManager::SetCurrentColor(glm::vec4 pColor)
{
	mColor = pColor;
}