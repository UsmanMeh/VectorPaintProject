#pragma once
#include <vector>
#include "ICommand.h"
#include <memory>
class CommandManager
{
private:
	std::vector<std::unique_ptr<ICommand>> CommandHistory;
	size_t m_index = 0;
	
	void Trim();
	void Clean();

public:
	void AddCommand(std::unique_ptr<ICommand> p_command);
	void Undo();
};