#pragma once

#include "Maths.h"
#include "LineRenderer.h"

//
class GameNode
{
public:

	Vec2 position;

	float radius;

	GameNode(Vec2 pos, float rad);

	void Update(float delta);

	void Draw(LineRenderer* lines);
};