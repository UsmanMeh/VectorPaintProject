#include "KeyboardController.h"

void KeyboardController::Initialize(SceneManager* pSceneManager)
{
	mSceneManager = pSceneManager;
}

void KeyboardController::UpdateEvent(SDL_Event event)
{
		const Uint8* state = SDL_GetKeyboardState(NULL);
	if (event.type == SDL_KEYDOWN)
	{
		if (state[SDL_SCANCODE_LCTRL] && state[SDL_SCANCODE_LSHIFT] && state[SDL_SCANCODE_Z])
		{
			mSceneManager->GetActvieScene()->mCommandManager->Redo();
		}
		else if (state[SDL_SCANCODE_LCTRL] && state[SDL_SCANCODE_Z])
		{
			mSceneManager->GetActvieScene()->mCommandManager->Undo();
		}
		KeyboardEvent(ButtonState::down, state);
	}
	if (event.type == SDL_KEYUP)
	{
		KeyboardEvent(ButtonState::up, state);
	}
}

void KeyboardController::Render()
{
}

void KeyboardController::Update()
{
}

void KeyboardController::KeyboardEvent(ButtonState pbuttonState, const Uint8* pKeyState)
{
	TrigerSubscribedCallback(pbuttonState, pKeyState);
}

void KeyboardController::SubscribeToKeyBoardEvent(std::function<void(ButtonState, const Uint8*)> pCallback)
{
	mKeyboardEventCallback.push_back(pCallback);
}

void KeyboardController::TrigerSubscribedCallback(ButtonState pbuttonState, const Uint8* pKeyState)
{
	for (auto& func : mKeyboardEventCallback)
	{
		func(pbuttonState, pKeyState);
	}
}
