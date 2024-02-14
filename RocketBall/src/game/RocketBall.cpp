#include <iostream>

#include "RocketBall.h"
#include "Circle.h"
#include "Box.h"
#include "CollisionFunctions.h"
#include "CollisionInfo.h"

RocketBall::RocketBall()
{
	m_gameNodes.push_back(new Circle(0, 0, 2, 2, { 0, 1, 0 }, false));
	m_gameNodes.push_back(new Box(5, -3, 2, 1, 1, { 0, 1, 0 }, false));
	m_gameNodes.push_back(new Circle(-3, 4, 1, 1, { 0, 1, 0 }, false));
	m_gameNodes.push_back(new Circle(-5, -12, 5, 5, { 0, 1, 0 }, false));
	m_gameNodes.push_back(new Box(5, 12, 4, 2, 2, { 0, 1, 0 }, false));

	// Get shapes from m_gameNodes
	for (int i = 0; i < m_gameNodes.size(); i++)
	{
		Shape* shape = dynamic_cast<Shape*>(m_gameNodes[i]);
		if (shape != nullptr)
		{
			m_shapes.push_back(shape);
		}
	}
}

void RocketBall::Update(float delta)
{
	// Input
	if (m_shapeOnMouse != nullptr)
	{
		m_shapeOnMouse->SetVelocity({ 0, 0 });
		m_shapeOnMouse->SetGlobalPos(cursorPos);
	}

	if (m_shapeToFling != nullptr)
	{
		lines->SetColour({ 1, 1, 1 });
		lines->DrawLineSegment(m_shapeToFling->GetGlobalPos(), cursorPos);
	}

	// Update
	for (int i = 0; i < m_gameNodes.size(); i++)
	{
		m_gameNodes[i]->Update(delta);
	}

	// Draw
	for (int i = 0; i < m_gameNodes.size(); i++)
	{
#if _DEBUG
		m_gameNodes[i]->DebugDraw(lines);
#endif
	}

	// Collisions
	std::vector<CollisionInfo> allCollisions;
	for (int i = 0; i < m_shapes.size(); i++)
	{
		for (int j = i + 1; j < m_shapes.size(); j++)
		{
			allCollisions.push_back(CollisionFunctions::CollideShapes(m_shapes[i], m_shapes[j]));
		}
	}

	for (CollisionInfo& collision : allCollisions)
	{
		CollisionFunctions::DepenetrateShapes(collision);
	}
}

void RocketBall::OnLeftClick()
{
	for (int i = 0; i < m_shapes.size(); i++)
	{
		if (CollisionFunctions::DoesPointHitShape(cursorPos, m_shapes[i]))
		{
			m_shapeOnMouse = m_shapes[i];
		}
	}
}

void RocketBall::OnLeftRelease()
{
	m_shapeOnMouse = nullptr;
}

void RocketBall::OnRightClick()
{
	for (int i = 0; i < m_shapes.size(); i++)
	{
		if (CollisionFunctions::DoesPointHitShape(cursorPos, m_shapes[i]))
		{
			m_shapeToFling = m_shapes[i];
		}
	}
}

void RocketBall::OnRightRelease()
{
	if (m_shapeToFling != nullptr)
	{
		Vec2 toCursor = cursorPos - m_shapeToFling->GetGlobalPos();
		m_shapeToFling->ApplyImpulse(toCursor * m_flingMultiplier);

		m_shapeToFling = nullptr;
	}
}

RocketBall::~RocketBall()
{
	for (int i = 0; i < m_gameNodes.size(); i++)
	{
		delete(m_gameNodes[i]);
	}
}
