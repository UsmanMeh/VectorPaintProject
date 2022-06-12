#pragma once
#include <SDL_events.h>
#include <functional>
#include "SceneManager.h"
#include "Input.h"
class KeyboardController : public KeyboardInput
{
private:
	SceneManager* mSceneManager;
	std::vector<std::function<void(ButtonState, const Uint8*)>> mKeyboardEventCallback;
public:
	void Initialize(SceneManager*);
	void UpdateEvent(SDL_Event event);
	void Render();
	void Update();
	void KeyboardEvent(ButtonState pbuttonState, const Uint8* pKeyState) override;
	void SubscribeToKeyBoardEvent(std::function<void(ButtonState, const Uint8*)>);
	void TrigerSubscribedCallback(ButtonState, const Uint8*);
};

