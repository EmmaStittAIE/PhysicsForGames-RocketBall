#pragma once
#include "Maths.h"
#include "LineRenderer.h"

class Application
{
public:
	virtual void Update(float delta) = 0;

	bool leftMouseDown;
	bool rightMouseDown;
	Vec2 cursorPos;
	LineRenderer* lines = nullptr;

	virtual void OnLeftClick() {}
	virtual void OnLeftRelease() {}
	virtual void OnRightClick() {}
	virtual void OnRightRelease() {}
};