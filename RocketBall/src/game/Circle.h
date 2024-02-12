#pragma once

#include "Shape.h"

class Circle : public Shape
{
public:
	float m_radius;

	Circle(float xPos, float yPos, float mass, float radius, bool useGrav = true, GameNode* parent = nullptr)
		: Shape(xPos, yPos, mass, useGrav, parent), m_radius(radius) {};
	Circle(Vec2 position, float mass, float radius, bool useGrav = true, GameNode* parent = nullptr)
		: Shape(position, mass, useGrav, parent), m_radius(radius) {};

	void DebugDraw(LineRenderer* lines) override;
};