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
Vector2D::Vector2D(int x, int y)
{
	this->x = static_cast<float>(x);
	this->y = static_cast<float>(y);
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
Vector2D& Vector2D::Subtract(const Vector2D& vec)
{
	this->x -= vec.x;
	this->y -= vec.y;

	return *this;
}
Vector2D& Vector2D::Subtract(float val)
{
	this->x -= val;
	this->y -= val;

	return *this;
}
Vector2D& Vector2D::Add(float val)
{
	this->x += val;
	this->y += val;

	return *this;
}
Vector2D& Vector2D::operator-=(const Vector2D& vec)
{
	return this->Subtract(vec);
}