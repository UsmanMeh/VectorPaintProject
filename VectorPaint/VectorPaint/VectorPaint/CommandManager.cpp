#include "CommandManager.h"
#include <string>
#include "Debug.h"
void CommandManager::AddCommand(std::shared_ptr<ICommand> p_command)
{
	if (m_index != CommandHistory.size())
	{
		Trim();
	}
	if (!CommandHistory.empty() && (CommandHistory.back())->Compair(p_command) > 0)
	{
		CommandHistory.back()->Merge(p_command);
	}
	else
	{
		p_command->Execute();
		CommandHistory.push_back(std::move(p_command));
		m_index++;
	}
}
void CommandManager::Redo()
{
	if (m_index < CommandHistory.size())
	{
		CommandHistory.at(m_index)->Redo();
		m_index++;
	}
}
void CommandManager::Undo()
{
	if (m_index > 0)
	{
		m_index--;
		CommandHistory.at(m_index)->Undo();
	}
}

void CommandManager::GetDebugList(std::vector<std::string>* pCommandHistoryDebug)
{
	for (size_t i = 0; i < m_index; i++)
	{
		pCommandHistoryDebug->push_back(CommandHistory.at(i)->Debug());
	}
}

void CommandManager::Trim()
{
	std::for_each(CommandHistory.begin() + m_index, CommandHistory.end(), [](std::shared_ptr<ICommand> elem) {
		elem->Clean();
		});
	CommandHistory.erase(CommandHistory.begin() + m_index, CommandHistory.end());
}
void CommandManager::Clean()
{
	CommandHistory.clear();
}