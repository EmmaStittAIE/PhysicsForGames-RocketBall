#pragma once

#include "GameNode.h"

// Temporarily built-in circle collider
class RigidBody : GameNode
{
public:
	
	// circle collider
	float radius;

	Vec2 velocity;
	Vec2 acceleration;

	RigidBody(Vec2 pos, float rad) : GameNode(pos), radius(rad)
	{

	}
};