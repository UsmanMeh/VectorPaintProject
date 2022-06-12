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
	Vector2D(int x, int y);
	Vector2D& Zero();
	Vector2D& One();

	Vector2D& Subtract(const Vector2D& vec);
	Vector2D& Subtract(float val);
	Vector2D& Add(float val);

	Vector2D& operator-=(const Vector2D& vec);

	void Debug()
	{
		std::cout << ToString() << std::endl;
	}
	std::string ToString()
	{
		return "( x = " + std::to_string(x) + " y = " + std::to_string(y)+" )";
	}
};