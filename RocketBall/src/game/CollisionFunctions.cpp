#include "CollisionFunctions.h"

#include "CollisionInfo.h"
#include "Shape.h"
#include "Circle.h"
#include "Logger.h"

CollisionInfo CollisionFunctions::CollideShapes(Shape* shape1, Shape* shape2)
{
	switch (shape1->m_shapeType)
	{
	case ShapeType::circle:
		switch (shape2->m_shapeType)
		{
		case ShapeType::circle:
			return CollideCircleWithCircle((Circle*)shape1, (Circle*)shape2);

		case ShapeType::box:
			//return CollideCircleWithBox((Circle*)shape1, (Box*)shape2);
			Logger::LogWarning("Collison between 'circle' and 'box' is not implimented");
			throw;

		case ShapeType::plane:
			//return CollideCircleWithPlane((Circle*)shape1, (Plane*)shape2);
			Logger::LogWarning("Collison between 'circle' and 'plane' is not implimented");
			throw;

		default:
			Logger::LogError("Shape 'shape2' does not contain a valid shape");
			throw;
		}

	default:
		Logger::LogError("Shape 'shape1' does not contain a valid shape");
		throw;
	}
}

CollisionInfo CollisionFunctions::CollideCircleWithCircle(Circle* shape1, Circle* shape2)
{
	CollisionInfo collision;
	Vec2 displacement = shape2->GetGlobalPos() - shape1->GetGlobalPos();

	// If displacement is <= the combined radius of both shapes, then a collision has occurred
	float combinedRad = shape1->m_radius + shape2->m_radius;
	if (glm::length(displacement) <= combinedRad)
	{
		// If a collision has occurred, then we want to fill out our CollisionInfo
		collision.shape1 = shape1;
		collision.shape2 = shape2;

		collision.penetrationDepth = combinedRad - glm::length(displacement);
		collision.normal = glm::normalize(displacement);
	}

	return collision;
}

void CollisionFunctions::DepenetrateShapes(CollisionInfo collision)
{
	if (collision.penetrationDepth >= 0)
	{
		collision.shape1->MovePos(-collision.normal * collision.penetrationDepth * 0.5f);
		collision.shape2->MovePos(collision.normal * collision.penetrationDepth * 0.5f);
	}
}

bool CollisionFunctions::DoesPointHitShape(Vec2 point, Shape* shape)
{
	switch (shape->m_shapeType)
	{
	case ShapeType::circle:
		return DoesPointHitCircle(point, (Circle*)shape);

	case ShapeType::box:
		//return DoesPointHitBox(point, (Box*)shape);
		Logger::LogWarning("'box' is not implemented");
		return false;

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

bool CollisionFunctions::DoesPointHitCircle(Vec2 point, Circle* circle)
{
	Vec2 displacement = point - circle->GetGlobalPos();

	return glm::length(displacement) <= circle->m_radius;
}
