#pragma once

#include "Maths.h"
#include "Shape.h"

struct CollisionInfo
{
	Shape* shape1 = nullptr;
	Shape* shape2 = nullptr;

	Vec2 normal = { 0, 0 };
	
	// If this is >= 0, then a collision has happened, so it should net be initialised in that range
	float penetrationDepth = -1;
};