#include "CollisionCircle.h"
#include "CollisionFunctions.h"
#include "CollisionInfo.h"
#include "Logger.h"

void CollisionCircle::DebugDraw(LineRenderer* lines)
{
	TransformNode::DebugDraw(lines);

	lines->SetColour(m_debugColour);
	lines->DrawCircle(GetGlobalPos(), m_radius);
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
