#pragma once

#include "CollisionShape.h"

class CollisionCircle : public CollisionShape
{
private:
	float m_radius;

public:
	CollisionCircle(float xPos, float yPos, float radius, Vec3 debugColour = { 255, 255, 255 })
		: CollisionShape(xPos, yPos, ShapeType::circle, debugColour), m_radius(radius) {};
	CollisionCircle(Vec2 position, float radius, Vec3 debugColour = { 255, 255, 255 })
		: CollisionShape(position, ShapeType::circle, debugColour), m_radius(radius) {};

	void DebugDraw(LineRenderer* lines, Vec2 cameraPos, Vec2 cameraHalfExtents) override;

	CollisionInfo CollideWithShape(CollisionShape* other) override;

	float GetRadius();
	void SetRadius(float radius);
};