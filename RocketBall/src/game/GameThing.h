#pragma once

#include "Maths.h"
#include "LineRenderer.h"

class GameThing
{
public:

	Vec2 position;

	float radius;

	GameThing(Vec2 pos, float rad);

	void Update(float delta);

	void Draw(LineRenderer* lines);
};