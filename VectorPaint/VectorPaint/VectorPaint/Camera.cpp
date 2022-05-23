#include "Camera.h"
float Camera::Zoom = 1;
float Camera::x = 0;
float Camera::y = 0;

void Camera::SetCameraPosition(float pX, float pY)
{
	x = pX;
	y = pY;
}
