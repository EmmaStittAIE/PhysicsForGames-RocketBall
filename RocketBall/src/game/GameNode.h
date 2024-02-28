#pragma once

#include <vector>

#include "Maths.h"
#include "LineRenderer.h"

class GameNode
{
protected:
	GameNode* m_parent = nullptr;

	std::vector<GameNode*> m_children;

	Vec3 m_debugColour;

public:
	GameNode(Vec3 debugColour = { 255, 255, 255 })
		: m_debugColour(debugColour / 255.0f) {};

	// Update with a fixed timestep
	virtual void Update(float delta) {};
	virtual void DebugDraw(LineRenderer* lines, Vec2 cameraPos, Vec2 cameraHalfExtents) {};

	GameNode* GetParent();

	const std::vector<GameNode*>* GetChildren();
	void AddChild(GameNode* child);
	void RemoveChild(GameNode* child);

	// In the colour format (R, G, B)
	void SetDebugColour(Vec3 debugColour);

	~GameNode();
};