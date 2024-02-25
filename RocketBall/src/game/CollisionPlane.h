#pragma once

#include "CollisionShape.h"

class CollisionPlane : public CollisionShape
{
private:
	// Normalised value
	Vec2 m_tangent;
	Vec2 m_normal;

	// Angle in radians
	float m_angle;

public:
	// Might need to trim this, looks a little cluttered
	CollisionPlane(float xPos, float yPos, float angle, Vec3 debugColour = { 1, 1, 1 })
		: CollisionShape(xPos, yPos, ShapeType::plane, debugColour), m_tangent(std::cos(angle), std::sin(angle)),
						 m_normal(-m_tangent.y, m_tangent.x), m_angle(angle) {};
	CollisionPlane(Vec2 position, float angle, Vec3 debugColour = { 1, 1, 1 })
		: CollisionShape(position, ShapeType::plane, debugColour), m_tangent(std::cos(angle), std::sin(angle)),
						 m_normal(-m_tangent.y, m_tangent.x), m_angle(angle) {};

	void DebugDraw(LineRenderer* lines, Vec2 cameraPos, Vec2 cameraHalfExtents) override;

	CollisionInfo CollideWithShape(CollisionShape* other) override;

	Vec2 GetTangent();
	Vec2 GetNormal();
	float GetAngle();
	void SetAngle(float angle);
};