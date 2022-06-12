#include "Camera.h"

float Camera::Zoom = 1;
float Camera::x = 0;
float Camera::y = 0;
float Camera::aspactRatio = 1.5f;
glm::mat4 Camera::ViewMatrix = glm::mat4(1.f);

void Camera::SetCameraPosition(float pX, float pY)
{
	x = pX;
	y = pY;
	Camera::UpdateViewMatrix();
}
void Camera::SetCameraZoom(float pZoom)
{
	Zoom = pZoom;
	Camera::UpdateViewMatrix();
}
void Camera::UpdateViewMatrix()
{
	Camera::ViewMatrix = glm::mat4(1.f);
	Camera::ViewMatrix = glm::translate(Camera::ViewMatrix, glm::vec3(Camera::x, Camera::y, 0));
	Camera::ViewMatrix = glm::scale(Camera::ViewMatrix, glm::vec3(Camera::Zoom, Camera::Zoom, 0));
}
void Camera::ConvertToCameraSpace(Vector2D* point)
{
	point->x -= Camera::x;
	point->y -= Camera::y;
	point->x /= Camera::Zoom;
	point->y /= Camera::Zoom;
}