#include "CollisionFunctions.h"

#include "CollisionInfo.h"
#include "CollisionShape.h"
#include "CollisionCircle.h"
#include "CollisionBox.h"
#include "Logger.h"

CollisionInfo CollisionFunctions::CollideShapes(CollisionShape* shape1, CollisionShape* shape2)
{
	switch (shape1->m_shapeType)
	{
	case ShapeType::circle:
		switch (shape2->m_shapeType)
		{
		case ShapeType::circle:
			return CollideCircleWithCircle((CollisionCircle*)shape1, (CollisionCircle*)shape2);

		case ShapeType::box:
			return CollideCircleWithBox((CollisionCircle*)shape1, (CollisionBox*)shape2);

		case ShapeType::plane:
			//return CollideCircleWithPlane((Circle*)circle1, (Plane*)circle2);
			Logger::LogWarning("Collison between 'circle' and 'plane' is not implemented");
			return CollisionInfo();

		default:
			Logger::LogError("Shape 'circle2' does not contain a valid shape");
			return CollisionInfo();
		}

	case ShapeType::box:
		switch (shape2->m_shapeType)
		{
		case ShapeType::circle:
			return CollideCircleWithBox((CollisionCircle*)shape2, (CollisionBox*)shape1);

		case ShapeType::box:
			return CollideBoxWithBox((CollisionBox*)shape1, (CollisionBox*)shape2);

		case ShapeType::plane:
			//return CollideBoxWithPlane((Box*)circle1, (Plane*)circle2);
			Logger::LogWarning("Collison between 'circle' and 'plane' is not implemented");
			return CollisionInfo();

		default:
			Logger::LogError("Shape 'circle2' does not contain a valid shape");
			return CollisionInfo();
		}

	default:
		Logger::LogError("Shape 'circle1' does not contain a valid shape");
		return CollisionInfo();
	}
}

CollisionInfo CollisionFunctions::CollideCircleWithCircle(CollisionCircle* circle1, CollisionCircle* circle2)
{
	CollisionInfo collision;

	Vec2 displacement = circle2->GetGlobalPos() - circle1->GetGlobalPos();

	// If displacement is <= the combined radius of both shapes, then a collision has occurred
	float combinedRad = circle1->GetRadius() + circle2->GetRadius();
	float distance = glm::length(displacement);
	if (distance <= combinedRad)
	{
		// If a collision has occurred, then we want to fill out our CollisionInfo
		collision.shape1 = circle1;
		collision.shape2 = circle2;

		collision.penetrationDepth = combinedRad - distance;
		collision.normal = glm::normalize(displacement);
	}

	return collision;
}

CollisionInfo CollisionFunctions::CollideCircleWithBox(CollisionCircle* circle, CollisionBox* box)
{
	CollisionInfo collision;

	Vec2 circlePos = circle->GetGlobalPos();
	Vec2 boxPos = box->GetGlobalPos();

	Vec2 halfExtents = { box->GetHalfWidth(), box->GetHalfHeight() };

	// Clamp box to the box's extents, relative to its position
	Vec2 clampedPoint = glm::clamp(circlePos, boxPos - halfExtents, boxPos + halfExtents);

	Vec2 displacement = clampedPoint - circlePos;
	float distance = glm::length(displacement);
	if (distance <= circle->GetRadius())
	{
		collision.shape1 = circle;
		collision.shape2 = box;

		collision.penetrationDepth = circle->GetRadius() - distance;
		collision.normal = glm::normalize(displacement);
	}

	return collision;
	return CollisionInfo();
}

CollisionInfo CollisionFunctions::CollideBoxWithBox(CollisionBox* box1, CollisionBox* box2)
{
	CollisionInfo collision;

	Vec2 positionB1 = box1->GetGlobalPos();
	Vec2 positionB2 = box2->GetGlobalPos();

	Vec2 halfExtentsB1 = { box1->GetHalfWidth(), box1->GetHalfHeight() };
	Vec2 halfExtentsB2 = { box2->GetHalfWidth(), box2->GetHalfHeight() };

	Vec2 minB1 = positionB1 - halfExtentsB1;
	Vec2 maxB1 = positionB1 + halfExtentsB1;
	Vec2 minB2 = positionB2 - halfExtentsB2;
	Vec2 maxB2 = positionB2 + halfExtentsB2;

	// Overlaps between R1/2 (right of box1/box2) and L2/1 (left of box2/box1)
	float overlapR1L2 = maxB1.x - minB2.x;
	float overlapR2L1 = maxB2.x - minB1.x;
	// Overlap between T1/2 (top of box1/box2) and B2/1 (bottom of box2/box1)
	float overlapT1B2 = maxB1.y - minB2.y;
	float overlapT2B1 = maxB2.y - minB1.y;

	// Find the smallest overlap
	float overlaps[4] = { overlapR1L2, overlapR2L1, overlapT1B2, overlapT2B1 };
	
	int indexOfSmallest = 0;
	for (int i = 1; i < 4; i++)
	{
		if (overlaps[i] < overlaps[indexOfSmallest])
		{
			indexOfSmallest = i;
		}
	}

	collision.shape1 = box1;
	collision.shape2 = box2;

	collision.penetrationDepth = overlaps[indexOfSmallest];

	switch (indexOfSmallest)
	{
	case 0:
		collision.normal = { 1, 0 };
		break;

	case 1:
		collision.normal = { -1, 0 };
		break;

	case 2:
		collision.normal = { 0, 1 };
		break;

	case 3:
		collision.normal = { 0, -1 };
		break;

	default:
		Logger::LogError("'indexOfSmallest' is out of bounds");
	}

	return collision;
	return CollisionInfo();
}

void CollisionFunctions::DepenetrateShapes(CollisionInfo collision)
{
	if (collision.penetrationDepth >= 0)
	{
		collision.shape1->MovePos(-collision.normal * collision.penetrationDepth * 0.5f);
		collision.shape2->MovePos(collision.normal * collision.penetrationDepth * 0.5f);
	}
}

bool CollisionFunctions::DoesPointHitShape(Vec2 point, CollisionShape* shape)
{
	switch (shape->m_shapeType)
	{
	case ShapeType::circle:
		return DoesPointHitCircle(point, (CollisionCircle*)shape);

	case ShapeType::box:
		return DoesPointHitBox(point, (CollisionBox*)shape);

	case ShapeType::plane:
		//return DoesPointHitPlane(point, (Plane*)shape);
		Logger::LogWarning("'plane' is not implemented");
		return false;

	default:
		Logger::LogError("Shape 'shape' does not contain a valid shape");
		return false;

	}

	return false;
}

bool CollisionFunctions::DoesPointHitCircle(Vec2 point, CollisionCircle* circle)
{
	Vec2 displacement = point - circle->GetGlobalPos();

	return glm::length(displacement) <= circle->GetRadius();
}

bool CollisionFunctions::DoesPointHitBox(Vec2 point, CollisionBox* box)
{
	/*Vec2 boxPos = box->GetGlobalPos();
	Vec2 halfExtents = { box->GetHalfWidth(), box->GetHalfHeight() };

	Vec2 clampedPoint = glm::clamp(point, boxPos - halfExtents, boxPos + halfExtents);

	return clampedPoint == point;*/
	return false;
}
