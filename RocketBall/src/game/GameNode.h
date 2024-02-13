#pragma once

#include <vector>

#include "Maths.h"
#include "LineRenderer.h"

class GameNode
{
protected:
	// TODO: implement scene tree
	GameNode* m_parent;

	std::vector<GameNode*> m_children;

	Vec2 m_localPosition;

public:
	std::string m_name;


	GameNode(float xPos, float yPos, GameNode* parent = nullptr) 
		: m_localPosition(xPos, yPos), m_parent(parent) {};
	GameNode(Vec2 pos, GameNode* parent = nullptr)
		: m_localPosition(pos), m_parent(parent) {};

	// Update with a fixed timestep
	virtual void Update(float delta) {};

	virtual void DebugDraw(LineRenderer* lines);

	// Position get/setters
	Vec2 GetGlobalPos();
	void SetGlobalPos(Vec2 pos);
	Vec2 GetLocalPos();
	void SetLocalPos(Vec2 pos);
	void MovePos(Vec2 distance);

	~GameNode();
};