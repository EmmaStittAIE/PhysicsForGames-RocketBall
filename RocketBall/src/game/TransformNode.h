#pragma once

#include "GameNode.h"

class TransformNode : public GameNode
{
protected:
	Vec2 m_localPosition;

public:
	TransformNode(float xPos, float yPos, Vec3 debugColour = { 255, 255, 255 })
		: GameNode(debugColour), m_localPosition(xPos, yPos) {};
	TransformNode(Vec2 pos, Vec3 debugColour = { 255, 255, 255 })
		: GameNode(debugColour), m_localPosition(pos) {};

	void DebugDraw(LineRenderer* lines, Vec2 cameraPos, Vec2 cameraHalfExtents) override;

	// Position get/setters
	Vec2 GetGlobalPos();
	void SetGlobalPos(Vec2 pos);
	Vec2 GetLocalPos();
	void SetLocalPos(Vec2 pos);
	void MovePos(Vec2 distance);
};