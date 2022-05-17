#pragma once
#include <iostream>
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
};
