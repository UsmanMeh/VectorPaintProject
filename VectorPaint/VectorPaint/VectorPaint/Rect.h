#pragma once
#include <iostream>
#include <string>
#include "Vector2D.h"
struct Rect
{
	float x;
	float y;
	float w;
	float h;
	Rect()
	{
		x = 0;
		y = 0;
		w = 1.0f;
		h = 1.0f;
	}
	Rect(float px, float py, float pw, float ph)
	{
		x = px;
		y = py;
		w = pw;
		h = ph;
	}
	void SetStart(Vector2D pStartPoint)
	{
		x = pStartPoint.x;
		y = pStartPoint.y;
	}
	void Debug()
	{
		std::cout << "x = " << x << " y = " << y << " w = " << w << " h = " << h << std::endl;
	}
	std::string ToString()
	{
		return "x = " + std::to_string(x) +" y = " + std::to_string(y )+ " w = " + std::to_string(w) +" h = " + std::to_string(h);
	}
	Vector2D GetOffset()
	{
		return Vector2D(x, y);
	}
};
