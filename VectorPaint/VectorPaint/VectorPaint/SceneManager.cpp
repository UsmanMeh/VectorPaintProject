#include "SceneManager.h"
void SceneManager::Initialize()
{
	scenes.emplace_back();
	activeScenes.push_back(scenes.front());
	for (auto it = activeScenes.begin(); it != activeScenes.end(); ++it)
	{
		it->Initialize();
	}
}
void SceneManager::Update()
{
	for (auto it = activeScenes.begin(); it != activeScenes.end(); ++it)
	{
		it->Update();
	}
}
void SceneManager::Render()
{
	for (auto it = activeScenes.begin(); it != activeScenes.end(); ++it)
	{
		it->Render();
	}
}
void SceneManager::RenderGUI()
{
	for (auto it = activeScenes.begin(); it != activeScenes.end(); ++it)
	{
		it->RenderGUI();
	}
}
void SceneManager::Clean()
{
	for (auto it = activeScenes.begin(); it != activeScenes.end(); ++it)
	{
		it->Clean();
	}
}

Scene* SceneManager::GetActvieScene()
{
	return &activeScenes[0];
}