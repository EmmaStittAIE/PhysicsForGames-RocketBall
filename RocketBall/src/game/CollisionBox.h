#pragma once

#include "CollisionShape.h"

class CollisionBox : public CollisionShape
{
private:
	float m_halfWidth;
	float m_halfHeight;

public:
	CollisionBox(float xPos, float yPos, float width, float height, Vec3 debugColour = { 255, 255, 255 })
		: CollisionShape(xPos, yPos, ShapeType::box, debugColour), m_halfWidth(width / 2), m_halfHeight(height / 2) {};
	CollisionBox(Vec2 position, float width, float height, Vec3 debugColour = { 255, 255, 255 })
		: CollisionShape(position, ShapeType::box, debugColour), m_halfWidth(width / 2), m_halfHeight(height / 2) {};

	void DebugDraw(LineRenderer* lines, Vec2 cameraPos, Vec2 cameraHalfExtents) override;

	CollisionInfo CollideWithShape(CollisionShape* other) override;

	float GetWidth();
	void SetWidth(float width);
	float GetHalfWidth();
	float GetHeight();
	void SetHeight(float height);
	float GetHalfHeight();
};