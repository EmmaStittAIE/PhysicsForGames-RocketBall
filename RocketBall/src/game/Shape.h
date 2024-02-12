#pragma once

#include "RigidBody.h"

enum ShapeType
{
	circle,
	box,
	plane
};

class Shape : public RigidBody
{
public:
	ShapeType type;

	Shape(float xPos, float yPos, float mass, bool useGrav = true, GameNode* parent = nullptr)
		: RigidBody(xPos, yPos, mass, useGrav, parent) {};
	Shape(Vec2 position, float mass, bool useGrav = true, GameNode* parent = nullptr)
		: RigidBody(position, mass, useGrav, parent) {};
};