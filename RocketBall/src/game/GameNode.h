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
	Vec3 m_debugColour;

	GameNode(Vec3 debugColour = { 255, 255, 255 })
		: m_debugColour(debugColour / 255.0f) {};

	// Update with a fixed timestep
	virtual void Update(float delta) {};
	virtual void DebugDraw(LineRenderer* lines, Vec2 cameraPos, Vec2 cameraHalfExtents) {};

	GameNode* GetParent();

	const std::vector<GameNode*>* GetChildren();
	void AddChild(GameNode* child);
	void RemoveChild(GameNode* child);

	~GameNode();
};