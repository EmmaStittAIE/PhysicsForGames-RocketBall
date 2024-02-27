#pragma once

#include <vector>

#include "Maths.h"
#include "LineRenderer.h"

class GameNode
{
protected:
	GameNode* m_parent = nullptr;

	std::vector<GameNode*> m_children;

public:
	std::string m_name;

	Vec3 m_debugColour;

	GameNode(Vec3 debugColour = { 1, 1, 1 })
		: m_debugColour(debugColour) {};

	// Update with a fixed timestep
	virtual void Update(float delta) {};
	virtual void DebugDraw(LineRenderer* lines, Vec2 cameraPos, Vec2 cameraHalfExtents) {};

	GameNode* GetParent();

	const std::vector<GameNode*>* GetChildren();
	void AddChild(GameNode* child);
	void RemoveChild(GameNode* child);

	~GameNode();
};