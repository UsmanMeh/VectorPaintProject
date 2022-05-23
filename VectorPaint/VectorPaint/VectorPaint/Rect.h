#pragma once
#include <iostream>
#include <string>
struct Rect
{
	float x;
	float y;
	float w;
	float h;

	Rect(float px, float py, float pw, float ph)
	{
		x = px;
		y = py;
		w = pw;
		h = ph;
	}
	void Debug()
	{
		std::cout << "x = " << x << " y = " << y << " w = " << w << " h = " << h << std::endl;
	}
	std::string ToString()
	{
		return "x = " + std::to_string(x) +" y = " + std::to_string(y )+ " w = " + std::to_string(w) +" h = " + std::to_string(h);
	}
};
