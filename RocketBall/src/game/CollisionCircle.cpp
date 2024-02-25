#include "CollisionCircle.h"
#include "CollisionFunctions.h"
#include "CollisionInfo.h"
#include "Logger.h"

void CollisionCircle::DebugDraw(LineRenderer* lines, Vec2 cameraPos, Vec2 cameraDimensions)
{
	TransformNode::DebugDraw(lines, cameraPos, cameraDimensions);

	Vec2 globalPos = GetGlobalPos();

	// Simplified box collision with the camera "box"
	Vec2 clampedPoint = glm::clamp(globalPos, cameraPos - cameraDimensions, cameraPos + cameraDimensions);

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
		//return CollideCircleWithPlane((Circle*)circle1, (Plane*)circle2);
		Logger::LogWarning("Collison between 'circle' and 'plane' is not implemented");
		return CollisionInfo();

	default:
		Logger::LogError("Shape 'circle2' does not contain a valid shape");
		return CollisionInfo();
	}
	return CollisionInfo();
}

float CollisionCircle::GetRadius()
{
	return m_radius;
}

void CollisionCircle::SetRadius(float radius)
{
	m_radius = radius;
}
