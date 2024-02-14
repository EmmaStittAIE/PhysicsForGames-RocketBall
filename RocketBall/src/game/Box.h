#pragma once

#include "Shape.h"

class Box : public Shape
{
private:
	float m_halfWidth;
	float m_halfHeight;

public:
	Box(float xPos, float yPos, float mass, float width, float height, Vec3 colour = { 1, 1, 1 }, bool useGrav = true, GameNode* parent = nullptr)
		: Shape(xPos, yPos, mass, ShapeType::box, colour, useGrav, parent), m_halfWidth(width / 2), m_halfHeight(height / 2) {};
	Box(Vec2 position, float mass, float width, float height, Vec3 colour = { 1, 1, 1 }, bool useGrav = true, GameNode* parent = nullptr)
		: Shape(position, mass, ShapeType::box, colour, useGrav, parent), m_halfWidth(width / 2), m_halfHeight(height / 2) {};

	void DebugDraw(LineRenderer* lines) override;

	float GetWidth();
	float GetHalfWidth();
	float GetHeight();
	float GetHalfHeight();
};