#pragma once

#include "CollisionShape.h"

class CollisionPlane : public CollisionShape
{
private:
	Vec2 m_normal;

	Vec2 GetTangent();
public:
	// Might need to trim this, looks a little cluttered
	CollisionPlane(float xPos, float yPos, float angle, Vec3 debugColour = { 1, 1, 1 })
		: CollisionShape(xPos, yPos, ShapeType::plane, debugColour), m_normal(-std::sin(angle * degToRad), std::cos(angle * degToRad)) {};
	CollisionPlane(Vec2 position, float angle, Vec3 debugColour = { 1, 1, 1 })
		: CollisionShape(position, ShapeType::plane, debugColour), m_normal(-std::sin(angle * degToRad), std::cos(angle * degToRad)) {};

	void DebugDraw(LineRenderer* lines, Vec2 cameraPos, Vec2 cameraHalfExtents) override;

	CollisionInfo CollideWithShape(CollisionShape* other) override;

	Vec2 GetNormal();
	void SetAngle(float angle);

	float GetDistFromOrigin();
};