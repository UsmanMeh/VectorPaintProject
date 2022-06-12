#pragma once
#include <gtc/matrix_transform.hpp>
#include "Vector2D.h"
class Camera
{
private:
public:
	static float Zoom;
	static float x;
	static float y;
	static glm::mat4 ViewMatrix;
	static float aspactRatio;
	static void SetCameraPosition(float pX, float pY);
	static void SetCameraZoom(float pZoom);
	static void UpdateViewMatrix();
	static void ConvertToCameraSpace(Vector2D* point);
};

