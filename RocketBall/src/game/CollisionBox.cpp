#include "CollisionBox.h"
#include "CollisionFunctions.h"
#include "CollisionInfo.h"
#include "Logger.h"

void CollisionBox::DebugDraw(LineRenderer* lines, Vec2 cameraPos, Vec2 cameraHalfExtents)
{
	TransformNode::DebugDraw(lines, cameraPos, cameraHalfExtents);

	Vec2 globalPos = GetGlobalPos();

	// Simplified box collision with the camera "box"
	Vec2 clampedPoint = glm::clamp(globalPos, cameraPos - cameraHalfExtents, cameraPos + cameraHalfExtents);

	if (CollisionFunctions::DoesPointHitBox(clampedPoint, this))
	{
		lines->SetColour(m_debugColour);

		Vec2 localCorners[4];

		localCorners[0] = { -m_halfWidth, m_halfHeight };
		localCorners[1] = { m_halfWidth, m_halfHeight };
		localCorners[2] = { m_halfWidth, -m_halfHeight };
		localCorners[3] = { -m_halfWidth, -m_halfHeight };

		for (int i = 0; i < std::size(localCorners); i++)
		{
			lines->AddPointToLine(localCorners[i] + globalPos);
		}
		lines->FinishLineLoop();
	}
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
		return CollisionFunctions::CollideBoxWithPlane(this, (CollisionPlane*)other);

	default:
		Logger::LogError("Shape 'other' does not contain a valid shape");
		return CollisionInfo();
	}
}

float CollisionBox::GetWidth()
{
	return m_halfWidth * 2;
}

void CollisionBox::SetWidth(float width)
{
	m_halfWidth = width / 2;
}

float CollisionBox::GetHalfWidth()
{
	return m_halfWidth;
}

float CollisionBox::GetHeight()
{
	return m_halfHeight * 2;
}

void CollisionBox::SetHeight(float height)
{
	m_halfHeight = height / 2;
}

float CollisionBox::GetHalfHeight()
{
	return m_halfHeight;
}
