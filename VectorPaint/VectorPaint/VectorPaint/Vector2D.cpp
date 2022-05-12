#include "Vector2D.h"
Vector2D::Vector2D()
{
	x = 0.0f;
	y = 0.0f;
}

Vector2D::Vector2D(float x, float y)
{
	this->x = x;
	this->y = y;
}
Vector2D& Vector2D::Zero()
{
	this->x = 0;
	this->y = 0;

	return *this;
}
Vector2D& Vector2D::One()
{
	this->x = 1;
	this->y = 1;

	return *this;
}