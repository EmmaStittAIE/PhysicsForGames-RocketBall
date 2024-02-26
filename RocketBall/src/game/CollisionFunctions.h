#pragma once

#include "Maths.h"

struct CollisionInfo;
class CollisionBody;
class CollisionShape;
class CollisionCircle;
class CollisionBox;
class CollisionPlane;

namespace CollisionFunctions
{
	// Collision detection
	extern CollisionInfo CollideCircleWithCircle(CollisionCircle* circle1, CollisionCircle* circle2);
	extern CollisionInfo CollideCircleWithBox(CollisionCircle* circle, CollisionBox* box);
	extern CollisionInfo CollideCircleWithPlane(CollisionCircle* circle, CollisionPlane* plane);

	extern CollisionInfo CollideBoxWithBox(CollisionBox* box1, CollisionBox* box2);
	extern CollisionInfo CollideBoxWithPlane(CollisionBox* box, CollisionPlane* plane);

	// Collision resolution
	extern void ResolveCollision(CollisionInfo collision);

	// Not called in CollideShapes
	extern bool DoesPointHitBody(Vec2 point, CollisionBody* body);
	extern bool DoesPointHitShape(Vec2 point, CollisionShape* shape);
	extern bool DoesPointHitCircle(Vec2 point, CollisionCircle* circle);
	extern bool DoesPointHitBox(Vec2 point, CollisionBox* box);
	extern bool DoesPointHitPlane(Vec2 point, CollisionPlane* plane);
};