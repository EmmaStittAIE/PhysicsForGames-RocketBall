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
	std::string m_name;

	Vec2 m_position;


	GameNode(float xPos, float yPos) 
		: m_position(xPos, yPos), m_parent(nullptr) {};
	GameNode(Vec2 pos)
		: m_position(pos), m_parent(nullptr) {};

	// Update with a fixed timestep
	virtual void Update(float delta) {};

	virtual void DebugDraw(LineRenderer* lines);

	virtual void CursorClickEvent(Vec2 cursorPos) {};
	virtual void CursorHoldEvent(Vec2 cursorPos) {};
	virtual void CursorReleaseEvent(Vec2 cursorPos) {};

	~GameNode();
};