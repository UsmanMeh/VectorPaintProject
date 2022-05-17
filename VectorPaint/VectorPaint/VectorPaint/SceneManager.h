#pragma once
#include <vector>
#include "Scene.h"
class SceneManager
{
private:
	std::vector <Scene> scenes;
	std::vector <Scene> activeScenes;

public:
	void Initialize();
	void Update();
	void Render();
	void RenderGUI();
	void Clean();

	Scene* GetActvieScene();
};

