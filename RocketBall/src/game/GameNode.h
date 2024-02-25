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

public:
	std::string m_name;

	Vec3 m_debugColour;

	GameNode(float xPos, float yPos, Vec3 debugColour = { 1, 1, 1 })
		: m_debugColour(debugColour), m_parent(nullptr) {};
	GameNode(Vec2 pos, Vec3 debugColour = { 1, 1, 1 })
		: m_debugColour(debugColour), m_parent(nullptr) {};

	// Update with a fixed timestep
	virtual void Update(float delta) {};
	virtual void DebugDraw(LineRenderer* lines, Vec2 cameraPos, Vec2 cameraDimensions) {};

	GameNode* GetParent();

	const std::vector<GameNode*>* GetChildren();
	void AddChild(GameNode* child);
	void RemoveChild(GameNode* child);

	~GameNode();
};