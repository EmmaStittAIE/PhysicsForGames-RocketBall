#pragma once

#include "CollisionShape.h"

class CollisionBox : public CollisionShape
{
private:
	float m_halfWidth;
	float m_halfHeight;

public:
	CollisionBox(float xPos, float yPos, float width, float height, Vec3 debugColour = { 1, 1, 1 })
		: CollisionShape(xPos, yPos, ShapeType::box, debugColour), m_halfWidth(width / 2), m_halfHeight(height / 2) {};
	CollisionBox(Vec2 position, float width, float height, Vec3 debugColour = { 1, 1, 1 })
		: CollisionShape(position, ShapeType::box, debugColour), m_halfWidth(width / 2), m_halfHeight(height / 2) {};

	void DebugDraw(LineRenderer* lines, Vec2 cameraPos, Vec2 cameraDimensions) override;

	CollisionInfo CollideWithShape(CollisionShape* other) override;

	float GetWidth();
	float GetHalfWidth();
	float GetHeight();
	float GetHalfHeight();
};