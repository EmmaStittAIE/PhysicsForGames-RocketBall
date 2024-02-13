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
protected:
	Shape(float xPos, float yPos, float mass, ShapeType type, Vec3 colour = { 1, 1, 1 }, bool useGrav = true, GameNode* parent = nullptr)
		: RigidBody(xPos, yPos, mass, useGrav, parent), m_shapeType(type), m_colour(colour) {};
	Shape(Vec2 position, float mass, ShapeType type, Vec3 colour = { 1, 1, 1 }, bool useGrav = true, GameNode* parent = nullptr)
		: RigidBody(position, mass, useGrav, parent), m_shapeType(type), m_colour(colour) {};

public:
	ShapeType m_shapeType;
	
	Vec3 m_colour;
};