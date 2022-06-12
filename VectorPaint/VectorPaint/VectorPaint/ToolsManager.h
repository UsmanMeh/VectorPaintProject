#pragma once
#include <iostream>
#include <map>
#include <algorithm>
#include <detail/type_vec.hpp>
#include<vec4.hpp>
class ToolsManager
{
	glm::vec4 mColor;
public:
	static ToolsManager* instance;
	static ToolsManager* GetInstance();
	void Initialize();
	enum Tools
	{
		Selection , Line, Square, Rectangle, Triangle, Circle , Path, size
	} SelectedTool;
	std::map<Tools, bool> ToolsList;
	std::map<Tools, std::string> ToolsNameList;
	Tools GetSelectedTool();
	void SetSelectedTool(Tools);
	glm::vec4 GetCurrentColor();
	void SetCurrentColor(glm::vec4);
};

