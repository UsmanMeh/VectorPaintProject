#pragma once
#include "iostream"
#include <string>
class Vector2D
{
public:
	float x;
	float y;

	Vector2D();
	Vector2D(float x, float y);
	Vector2D& Zero();
	Vector2D& One();

	void Debug()
	{
		std::cout << "x = " << x << "y = " << y << std::endl;
	}
	std::string ToString()
	{
		return "x = " + std::to_string(x) + "y = " + std::to_string(y);
	}
};