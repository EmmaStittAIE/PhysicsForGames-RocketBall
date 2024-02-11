#pragma once

#include <vector>

#include "Maths.h"
#include "LineRenderer.h"

class GameNode
{
private:
	// TODO: implement scene tree
	GameNode* m_parent;

	std::vector<GameNode*> m_children;

public:
	std::string name;

	Vec2 position;


	GameNode(float xPos, float yPos) 
		: position(xPos, yPos), m_parent(nullptr) {};
	GameNode(Vec2 pos)
		: position(pos), m_parent(nullptr) {};

	virtual void Update(float delta) {};

	virtual void FixedUpdate(float fixedDelta) {};

	virtual void DebugDraw(LineRenderer* lines);
};