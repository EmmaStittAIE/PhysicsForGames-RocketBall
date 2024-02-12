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

	Vec2 m_localPosition;


	GameNode(float xPos, float yPos, GameNode* parent = nullptr) 
		: m_localPosition(xPos, yPos), m_parent(parent) {};
	GameNode(Vec2 pos, GameNode* parent = nullptr)
		: m_localPosition(pos), m_parent(parent) {};

	// Update with a fixed timestep
	virtual void Update(float delta) {};

	virtual void DebugDraw(LineRenderer* lines);

	virtual void CursorClickEvent(Vec2 cursorPos) {};
	virtual void CursorHoldEvent(Vec2 cursorPos) {};
	virtual void CursorReleaseEvent(Vec2 cursorPos) {};

	Vec2 GetGlobalPos();

	~GameNode();
};