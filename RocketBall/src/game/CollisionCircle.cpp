#include "CollisionCircle.h"
#include "CollisionFunctions.h"
#include "CollisionInfo.h"
#include "Logger.h"

void CollisionCircle::DebugDraw(LineRenderer* lines, Vec2 cameraPos, Vec2 cameraHalfExtents)
{
	TransformNode::DebugDraw(lines, cameraPos, cameraHalfExtents);

	Vec2 globalPos = GetGlobalPos();

	// Simplified box collision with the camera "box"
	Vec2 clampedPoint = glm::clamp(globalPos, cameraPos - cameraHalfExtents, cameraPos + cameraHalfExtents);

	if (CollisionFunctions::DoesPointHitCircle(clampedPoint, this))
	{
		lines->SetColour(m_debugColour);
		lines->DrawCircle(globalPos, m_radius);
	}
}

CollisionInfo CollisionCircle::CollideWithShape(CollisionShape* other)
{
	switch (other->m_shapeType)
	{
	case ShapeType::circle:
		return CollisionFunctions::CollideCircleWithCircle(this, (CollisionCircle*)other);

	case ShapeType::box:
		return CollisionFunctions::CollideCircleWithBox(this, (CollisionBox*)other);

	case ShapeType::plane:
		return CollisionFunctions::CollideCircleWithPlane(this, (CollisionPlane*)other);

	default:
		Logger::LogError("Shape 'other' does not contain a valid shape");
		return CollisionInfo();
	}
}

float CollisionCircle::GetRadius()
{
	return m_radius;
}

void CollisionCircle::SetRadius(float radius)
{
	m_radius = radius;
}
