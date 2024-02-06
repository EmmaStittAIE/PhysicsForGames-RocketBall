#pragma once

#include <vector>

#include "Maths.h"
#include "LineRenderer.h"

class GameNode
{
public:

	GameNode* parent;

	std::vector<GameNode*> children;

	std::string name;

	Vec2 position;


	GameNode(float xPos, float yPos) : position(xPos, yPos) {};
	GameNode(Vec2 pos) : position(pos) {};

	virtual void Update(float delta) {};

	virtual void DebugDraw(LineRenderer* lines);
};