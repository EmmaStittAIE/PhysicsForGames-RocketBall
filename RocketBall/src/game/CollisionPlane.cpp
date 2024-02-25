#include "CollisionPlane.h"
#include "CollisionInfo.h"

void CollisionPlane::DebugDraw(LineRenderer* lines, Vec2 cameraPos, Vec2 cameraHalfExtents)
{
	TransformNode::DebugDraw(lines, cameraPos, cameraHalfExtents);
	
	// I was going to do a whole thing here where I clipped the line to the exact edges of the camera, but I figured
	// just setting the length to the maximum length it would need to be to fill the screen would be much faster
	lines->SetColour(m_debugColour);

	Vec2 globalPos = GetGlobalPos();

	float halfLineLength = std::sqrt((cameraHalfExtents.x * cameraHalfExtents.x) + (cameraHalfExtents.y * cameraHalfExtents.y));
	Vec2 halfTangent = m_tangent * halfLineLength;

	lines->DrawLineSegment(globalPos - halfTangent, globalPos + halfTangent);
	lines->DrawLineSegment(globalPos, globalPos + GetNormal());
}

CollisionInfo CollisionPlane::CollideWithShape(CollisionShape* other)
{
	//TODO: implement plane collisions
	switch (other->m_shapeType)
	{
	case ShapeType::circle:
		//return CollisionFunctions::CollideCircleWithPlane((CollisionCircle*)other, this);
		return CollisionInfo();

	case ShapeType::box:
		//return CollisionFunctions::CollideBoxWithPlane((CollisionBox*)other, this);
		return CollisionInfo();

	case ShapeType::plane:
		// No need to do anything here, as both planes must be static
		return CollisionInfo();

	default:
		//Logger::LogError("Shape 'circle2' does not contain a valid shape");
		return CollisionInfo();
	}
}

Vec2 CollisionPlane::GetTangent()
{
	return m_tangent;
}

Vec2 CollisionPlane::GetNormal()
{
	return m_normal;
}

float CollisionPlane::GetAngle()
{
	return m_angle;
}

void CollisionPlane::SetAngle(float angle)
{
	m_angle = angle;
	m_tangent = Vec2(std::cos(angle), std::sin(angle));
	m_normal = Vec2(-m_tangent.y, m_tangent.x);
}
