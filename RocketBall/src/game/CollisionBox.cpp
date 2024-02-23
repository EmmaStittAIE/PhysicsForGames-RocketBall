#include "CollisionBox.h"
#include "CollisionFunctions.h"
#include "CollisionInfo.h"
#include "Logger.h"

void CollisionBox::DebugDraw(LineRenderer* lines)
{
	TransformNode::DebugDraw(lines);

	lines->SetColour(m_debugColour);

	Vec2 localCorners[4];

	localCorners[0] = { -m_halfWidth, m_halfHeight };
	localCorners[1] = { m_halfWidth, m_halfHeight };
	localCorners[2] = { m_halfWidth, -m_halfHeight };
	localCorners[3] = { -m_halfWidth, -m_halfHeight };

	Vec2 globalPos = GetGlobalPos();
	for (int i = 0; i < std::size(localCorners); i++)
	{
		lines->AddPointToLine(localCorners[i] + globalPos);
	}
	lines->FinishLineLoop();
}

CollisionInfo CollisionBox::CollideWithShape(CollisionShape* other)
{
	switch (other->m_shapeType)
	{
	case ShapeType::circle:
		return CollisionFunctions::CollideCircleWithBox((CollisionCircle*)other, this);

	case ShapeType::box:
		return CollisionFunctions::CollideBoxWithBox(this, (CollisionBox*)other);

	case ShapeType::plane:
		//return CollideBoxWithPlane((Circle*)circle1, (Plane*)circle2);
		Logger::LogWarning("Collison between 'circle' and 'plane' is not implemented");
		return CollisionInfo();

	default:
		Logger::LogError("Shape 'circle2' does not contain a valid shape");
		return CollisionInfo();
	}
	return CollisionInfo();
}

float CollisionBox::GetWidth()
{
	return m_halfWidth * 2;
}

float CollisionBox::GetHalfWidth()
{
	return m_halfWidth;
}

float CollisionBox::GetHeight()
{
	return m_halfHeight * 2;
}

float CollisionBox::GetHalfHeight()
{
	return m_halfHeight;
}
