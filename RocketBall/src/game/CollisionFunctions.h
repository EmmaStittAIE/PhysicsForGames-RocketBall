#pragma once

#include "Maths.h"

struct CollisionInfo;
class CollisionShape;
class CollisionCircle;
class CollisionBox;
class CollisionPlane;

namespace CollisionFunctions
{
	// Collision detection
	extern CollisionInfo CollideCircleWithCircle(CollisionCircle* shape1, CollisionCircle* shape2);
	extern CollisionInfo CollideCircleWithBox(CollisionCircle* shape1, CollisionBox* shape2);
	extern CollisionInfo CollideCircleWithPlane(CollisionCircle* shape1, CollisionPlane* shape2);

	extern CollisionInfo CollideBoxWithBox(CollisionBox* shape1, CollisionBox* shape2);
	extern CollisionInfo CollideBoxWithPlane(CollisionBox* shape1, CollisionPlane* shape2);

	// Collision resolution
	extern void DepenetrateShapes(CollisionInfo collision);

	// Not called in CollideShapes
	extern bool DoesPointHitShape(Vec2 point, CollisionShape* shape);
	extern bool DoesPointHitCircle(Vec2 point, CollisionCircle* circle);
	extern bool DoesPointHitBox(Vec2 point, CollisionBox* box);
	extern bool DoesPointHitPlane(Vec2 point, CollisionPlane* plane);
};