#pragma once

#include "Maths.h"

struct CollisionInfo;
class Shape;
class Circle;
class Box;
class Plane;

namespace CollisionFunctions
{
	// Collision detection
	extern CollisionInfo CollideShapes(Shape* shape1, Shape* shape2);

	extern CollisionInfo CollideCircleWithCircle(Circle* shape1, Circle* shape2);
	extern CollisionInfo CollideCircleWithBox(Circle* shape1, Box* shape2);
	extern CollisionInfo CollideCircleWithPlane(Circle* shape1, Plane* shape2);

	extern CollisionInfo CollideBoxWithBox(Box* shape1, Box* shape2);
	extern CollisionInfo CollideBoxWithPlane(Box* shape1, Plane* shape2);

	// Collision resolution
	extern void DepenetrateShapes(CollisionInfo collision);

	// Not called in CollideShapes
	extern bool DoesPointHitShape(Vec2 point, Shape* shape);
	extern bool DoesPointHitCircle(Vec2 point, Circle* circle);
	extern bool DoesPointHitBox(Vec2 point, Box* box);
	extern bool DoesPointHitPlane(Vec2 point, Plane* plane);
};