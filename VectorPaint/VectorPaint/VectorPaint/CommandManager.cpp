#include "CommandManager.h"

void CommandManager::AddCommand(std::unique_ptr<ICommand> p_command)
{
	if (m_index != CommandHistory.size())
	{
		Trim();
	}
	p_command->Execute();
	CommandHistory.push_back(std::move(p_command));
	m_index++;
}
void CommandManager::Undo()
{
	CommandHistory.at(m_index)->Undo();
	m_index--;
}

void CommandManager::Trim()
{
	CommandHistory.erase(CommandHistory.begin() + m_index, CommandHistory.end());
}
void CommandManager::Clean()
{
	CommandHistory.clear();
}