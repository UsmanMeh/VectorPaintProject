#pragma once
#include "SDL_keycode.h"
enum class ButtonState : std::size_t
{
	down,
	up,
};
enum class MouseButton : std::size_t
{
	left,
	right,
	middle,
	none
};
class MouseInput
{
public:
	virtual void MouseEvent(ButtonState ms, MouseButton mb, Vector2D position) = 0;

};
class KeyboardInput
{
public:
	virtual void KeyboardEvent(ButtonState pbuttonState , const Uint8* pKeyState) = 0;

};