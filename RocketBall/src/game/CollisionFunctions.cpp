#include "CollisionFunctions.h"

#include "CollisionInfo.h"
#include "CollisionBody.h"
#include "PhysicsBody.h"
#include "CollisionShape.h"
#include "CollisionCircle.h"
#include "CollisionBox.h"
#include "CollisionPlane.h"
#include "Logger.h"

CollisionInfo CollisionFunctions::CollideCircleWithCircle(CollisionCircle* circle1, CollisionCircle* circle2)
{
	CollisionInfo collision;

	Vec2 displacement = circle2->GetGlobalPos() - circle1->GetGlobalPos();

	// If displacement is <= the combined radius of both shapes, then a collision has occurred
	float combinedRad = circle1->GetRadius() + circle2->GetRadius();
	float distance = glm::length(displacement);
	
	// Fill out collision info regardless - collision resolution later will ignore it if the depth is negative
	collision.shape1 = circle1;
	collision.shape2 = circle2;

	collision.penetrationDepth = combinedRad - distance;
	collision.normal = glm::normalize(displacement);

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
	
	// Fill out collision info
	if (distance == 0)
	{
		// Find the closest point on the edge of the box
		float distanceToEdges[4]
		{
			std::abs(boxPos.x + halfExtents.x - circlePos.x),		// Right
			std::abs(boxPos.x - halfExtents.x - circlePos.x),		// Left
			std::abs(boxPos.y + halfExtents.y - circlePos.y),		// Top
			std::abs(boxPos.y - halfExtents.y - circlePos.y)		// Bottom
		};

		// Find the smallest distance (smallest of 4 numbers actually has a second use, who knew)
		int indexOfSmallest = 0;
		for (int i = 1; i < 4; i++)
		{
			if (distanceToEdges[i] < distanceToEdges[indexOfSmallest])
			{
				indexOfSmallest = i;
			}
		}

		// Fill out collision info
		collision.shape1 = circle;
		collision.shape2 = box;

		collision.penetrationDepth = distanceToEdges[indexOfSmallest] + circle->GetRadius();

		// for some reason, these normals have to be the opposite of the AABB <-> AABB ones?
		// perhaps because box is in place of shape2 here...
		switch (indexOfSmallest)
		{
		case 0:
			collision.normal = { -1, 0 };
			break;

		case 1:
			collision.normal = { 1, 0 };
			break;

		case 2:
			collision.normal = { 0, -1 };
			break;

		case 3:
			collision.normal = { 0, 1 };
			break;

		default:
			Logger::LogError("'indexOfSmallest' is out of bounds");
		}
	}
	else
	{
		collision.shape1 = circle;
		collision.shape2 = box;

		collision.penetrationDepth = circle->GetRadius() - distance;
		collision.normal = glm::normalize(displacement);
	}

	return collision;
}

CollisionInfo CollisionFunctions::CollideCircleWithPlane(CollisionCircle* circle, CollisionPlane* plane)
{
	CollisionInfo collision;

	collision.shape1 = circle;
	collision.shape2 = plane;

	collision.penetrationDepth = -(glm::dot(circle->GetGlobalPos(), plane->GetNormal()) - plane->GetDistFromOrigin() - circle->GetRadius());
	// The normal needs to be reversed, as the plane is going to be treated as "shape2"
	collision.normal = -plane->GetNormal();

	return collision;
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

	float overlaps[4]
	{
		maxB1.x - minB2.x,		// Right1 vs Left2
		maxB2.x - minB1.x,		// Right2 vs Left1
		maxB1.y - minB2.y,		// Top1 vs Bottom2
		maxB2.y - minB1.y		// Top2 vs Bottom1
	};

	// Find the smallest overlap
	int indexOfSmallest = 0;
	for (int i = 1; i < 4; i++)
	{
		if (overlaps[i] < overlaps[indexOfSmallest])
		{
			indexOfSmallest = i;
		}
	}

	// Fill out collision info
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
}

CollisionInfo CollisionFunctions::CollideBoxWithPlane(CollisionBox* box, CollisionPlane* plane)
{
	CollisionInfo collision;

	Vec2 boxGlobalPos = box->GetGlobalPos();
	Vec2 boxHalfExtents = { box->GetHalfWidth(), box->GetHalfHeight() };

	Vec2 planeNormal = plane->GetNormal();
	float planeDistFromOrigin = plane->GetDistFromOrigin();

	Vec2 boxPoints[4]
	{
		boxGlobalPos - Vec2(boxHalfExtents.x, boxHalfExtents.y),
		boxGlobalPos - Vec2(boxHalfExtents.x, -boxHalfExtents.y),
		boxGlobalPos - Vec2(-boxHalfExtents.x, -boxHalfExtents.y),
		boxGlobalPos - Vec2(-boxHalfExtents.x, boxHalfExtents.y)
	};
	
	float deepestCollision = -FLT_MAX;
	for (int i = 1; i < 4; i++)
	{
		float collisionDepth = -(glm::dot(boxPoints[i], planeNormal) - planeDistFromOrigin);

		if (collisionDepth > deepestCollision)
		{
			deepestCollision = collisionDepth;
		}
	}

	collision.shape1 = box;
	collision.shape2 = plane;

	collision.penetrationDepth = deepestCollision;
	// The normal needs to be reversed, as the plane is going to be treated as "shape2"
	collision.normal = -plane->GetNormal();

	return collision;
}

// TODO: fix reversed normal for plane, despite plane's normal value  being the correct way round
void CollisionFunctions::ResolveCollision(CollisionInfo collision)
{
	if (collision.penetrationDepth >= 0)
	{
		// Gotta be a better way of doing this...
		PhysicsBody* physBod1 = collision.shape1->GetParentPB();
		PhysicsBody* physBod2 = collision.shape2->GetParentPB();

		if (physBod1 != nullptr && physBod1->IsKinematic() == false)
		{
			if (physBod2 != nullptr && physBod2->IsKinematic() == false)
			{
				float pb1Mass = physBod1->GetMass();
				float pb2Mass = physBod2->GetMass();
				float totalMass = pb1Mass + pb2Mass;

				physBod1->MovePos(-collision.normal * collision.penetrationDepth * (pb1Mass / totalMass));
				physBod2->MovePos(collision.normal * collision.penetrationDepth * (pb2Mass / totalMass));
			}
			else
			{
				physBod1->MovePos(-collision.normal * collision.penetrationDepth);
			}
		}
		else
		{
			if (physBod2 != nullptr && physBod2->IsKinematic() == false)
			{
				physBod2->MovePos(collision.normal * collision.penetrationDepth);
			}
		}
	}
}

bool CollisionFunctions::DoesPointHitBody(Vec2 point, CollisionBody* body)
{
	CollisionShape* bodyShape = dynamic_cast<CollisionShape*>(body);
	if (bodyShape != nullptr)
	{
		return DoesPointHitShape(point, bodyShape);
	}

	PhysicsBody* bodyPB = dynamic_cast<PhysicsBody*>(body);
	if (bodyPB != nullptr)
	{
		for (CollisionShape* shape : *bodyPB->GetCollisionShapes())
		{
			if (DoesPointHitShape(point, shape))
			{
				return true;
			}
		}
		return false;
	}

	return false;
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
		return DoesPointHitPlane(point, (CollisionPlane*)shape);

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
	Vec2 boxPos = box->GetGlobalPos();
	Vec2 halfExtents = { box->GetHalfWidth(), box->GetHalfHeight() };

	Vec2 clampedPoint = glm::clamp(point, boxPos - halfExtents, boxPos + halfExtents);

	return clampedPoint == point;
}

bool CollisionFunctions::DoesPointHitPlane(Vec2 point, CollisionPlane* plane)
{

	return (glm::dot(point, plane->GetNormal()) - plane->GetDistFromOrigin()) < 0;
}
