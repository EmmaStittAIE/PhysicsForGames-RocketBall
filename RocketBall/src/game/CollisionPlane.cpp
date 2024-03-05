#include "CollisionPlane.h"
#include "CollisionFunctions.h"
#include "CollisionInfo.h"
#include "Logger.h"

Vec2 CollisionPlane::GetTangent()
{
	return Vec2(m_normal.y, -m_normal.x);
}

void CollisionPlane::DebugDraw(LineRenderer* lines, Vec2 cameraPos, Vec2 cameraHalfExtents)
{	
	// If the plane is within a circle around the camera's corners, then we bother drawing it
	// Would love to do some kind of complex culling here, but it's not worth the time investment
	float maxDistToDrawSquared = std::pow(cameraHalfExtents.x, 2) + std::pow(cameraHalfExtents.y, 2);

	if (std::pow(GetDistFromPoint(cameraPos), 2) <= maxDistToDrawSquared)
	{
		lines->SetColour(m_debugColour);

		Vec2 globalPos = GetGlobalPos();

		// Magic number because some set limit is required if I don't do the fancy culling technique
		float halfLineLength = 2000;
		Vec2 halfTangent = GetTangent() * halfLineLength;

		lines->DrawLineSegment(globalPos - halfTangent, globalPos + halfTangent);
		lines->DrawLineSegment(globalPos, globalPos + m_normal);
	}
}

CollisionInfo CollisionPlane::CollideWithShape(CollisionShape* other)
{
	switch (other->m_shapeType)
	{
	case ShapeType::circle:
		return CollisionFunctions::CollideCircleWithPlane((CollisionCircle*)other, this);

	case ShapeType::box:
		return CollisionFunctions::CollideBoxWithPlane((CollisionBox*)other, this);
		return CollisionInfo();

	case ShapeType::plane:
		// No need to do anything here, as both planes must be static
		return CollisionInfo();

	default:
		Logger::LogError("Shape 'other' does not contain a valid shape");
		return CollisionInfo();
	}
}

Vec2 CollisionPlane::GetNormal()
{
	return m_normal;
}

// In degrees
void CollisionPlane::SetAngle(float angle)
{
	float radAngle = angle * degToRad;
	m_normal = Vec2(-std::sin(radAngle), std::cos(radAngle));
}

float CollisionPlane::GetDistFromPoint(Vec2 point)
{
	return glm::dot(point, m_normal) - GetDistFromOrigin();
}

float CollisionPlane::GetDistFromOrigin()
{
	return glm::dot(GetGlobalPos(), m_normal);
}
