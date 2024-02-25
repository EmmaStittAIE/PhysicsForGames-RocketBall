#pragma once
#include "Maths.h"
#include "LineRenderer.h"

class Application
{
public:
	// janky update to pass along the window's dimensions for drawing
	virtual void Update(Vec2 cameraPos, Vec2 cameraHalfExtents, float delta) = 0;

	bool leftMouseDown;
	bool rightMouseDown;
	Vec2 cursorPos;
	LineRenderer* lines = nullptr;

	virtual void OnLeftClick() {}
	virtual void OnLeftRelease() {}
	virtual void OnRightClick() {}
	virtual void OnRightRelease() {}
};