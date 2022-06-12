#pragma once
#include <vector>
#include "ICommand.h"
#include <string>
#include <memory>
class CommandManager
{
private:
	std::vector<std::shared_ptr<ICommand>> CommandHistory;
	size_t m_index = 0;
	
	void Trim();
	void Clean();

public:
	void AddCommand(std::shared_ptr<ICommand> p_command);
	void Redo();
	void Undo();
	void GetDebugList(std::vector<std::string>* pCommandHistory);
};