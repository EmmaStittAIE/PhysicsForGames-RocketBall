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
	// I was going to do a whole thing here where I clipped the line to the exact edges of the camera, but I figured
	// just setting the length to the maximum length it would need to be to fill the screen would be much faster
	lines->SetColour(m_debugColour);

	Vec2 globalPos = GetGlobalPos();

	float halfLineLength = std::sqrt((cameraHalfExtents.x * cameraHalfExtents.x) + (cameraHalfExtents.y * cameraHalfExtents.y));
	Vec2 halfTangent = GetTangent() * halfLineLength;

	// Since we're ignoring the position of the plane, we want to use the offset from the global centre instead
	lines->DrawLineSegment(globalPos - halfTangent, globalPos + halfTangent);
	lines->DrawLineSegment(globalPos, globalPos + m_normal);
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

float CollisionPlane::GetDistFromOrigin()
{
	return glm::dot(GetGlobalPos(), m_normal);
}
