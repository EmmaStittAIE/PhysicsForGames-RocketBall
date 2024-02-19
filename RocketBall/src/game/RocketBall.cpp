#include <iostream>

#include "RocketBall.h"
#include "PhysicsBody.h"
#include "CollisionShape.h"
#include "CollisionCircle.h"
//#include "CollisionBox.h"
#include "CollisionFunctions.h"
#include "CollisionInfo.h"

RocketBall::RocketBall()
	: m_rootNode(0, 0)
{
	// Create GameNodes from the bottom up (this will not be needed when editing tools are added later)
	CollisionCircle* collisionCircle1 = new CollisionCircle(0, 0, 2, { 1, 0.5f, 0 });
	PhysicsBody* physicsBody1 = new PhysicsBody(0, 0, 2, true, false);
	physicsBody1->AddChild(collisionCircle1);
	physicsBody1->AddCollisionShape(collisionCircle1);

	//CollisionBox* collisionBox1 = new CollisionBox(5, -3, 2, 1, 1, { 0, 1, 0 });

	CollisionCircle* collisionCircle2 = new CollisionCircle(-3, 4, 1, { 0, 1, 0 });

	CollisionCircle* collisionCircle3 = new CollisionCircle(-5, -12, 5, { 0, 1, 0 });

	//CollisionBox* collisionBox2 = new CollisionBox(5, 12, 4, 2, 2, { 0, 1, 0 });

	m_rootNode.AddChild(physicsBody1);
	//m_rootNode.AddChild(collisionBox1);
	m_rootNode.AddChild(collisionCircle2);
	m_rootNode.AddChild(collisionCircle3);
	//m_rootNode.AddChild(collisionBox2);

	// Get shapes from m_gameNodes
	m_collisionShapes = GetShapesFromChildren(&m_rootNode);
}

void RocketBall::Update(float delta)
{
	// Input
	if (m_bodyOnMouse != nullptr)
	{
		m_bodyOnMouse->SetVelocity({ 0, 0 });
		m_bodyOnMouse->SetGlobalPos(cursorPos);
	}

	if (m_bodyToFling != nullptr)
	{
		lines->SetColour({ 1, 0, 0 });
		lines->DrawLineSegment(m_bodyToFling->GetGlobalPos(), cursorPos);
	}

	// Update
	UpdateChildren(&m_rootNode, delta);

	// DebugDraw
#if _DEBUG
	DebugDrawChildren(&m_rootNode);
#endif

	// Collisions
	for (int repeats = 0; repeats < 10; repeats++)
	{
		std::vector<CollisionInfo> allCollisions;
		for (int i = 0; i < m_collisionShapes.size(); i++)
		{
			for (int j = i + 1; j < m_collisionShapes.size(); j++)
			{
				allCollisions.push_back(CollisionFunctions::CollideShapes(m_collisionShapes[i], m_collisionShapes[j]));
			}
		}

		for (CollisionInfo& collision : allCollisions)
		{
			CollisionFunctions::DepenetrateShapes(collision);
		}
	}
}

void RocketBall::OnLeftClick()
{
	for (int i = 0; i < m_collisionShapes.size(); i++)
	{
		if (CollisionFunctions::DoesPointHitShape(cursorPos, m_collisionShapes[i]))
		{
			PhysicsBody* shapePB = m_collisionShapes[i]->GetParentPB();
			if (shapePB != nullptr)
			{
				m_bodyOnMouse = shapePB;
			}
		}
	}
}

void RocketBall::OnLeftRelease()
{
	m_bodyOnMouse = nullptr;
}

void RocketBall::OnRightClick()
{
	for (int i = 0; i < m_collisionShapes.size(); i++)
	{
		if (CollisionFunctions::DoesPointHitShape(cursorPos, m_collisionShapes[i]))
		{
			PhysicsBody* shapePB = m_collisionShapes[i]->GetParentPB();
			if (shapePB != nullptr)
			{
				m_bodyToFling = shapePB;
			}
		}
	}
}

void RocketBall::OnRightRelease()
{
	if (m_bodyToFling != nullptr)
	{
		Vec2 toCursor = cursorPos - m_bodyToFling->GetGlobalPos();
		m_bodyToFling->ApplyImpulse(toCursor * m_flingMultiplier);

		m_bodyToFling = nullptr;
	}
}

void RocketBall::UpdateChildren(GameNode* root, float delta)
{
	std::vector<GameNode*> children = *root->GetChildren();

	for (int i = 0; i < children.size(); i++)
	{
		UpdateChildren(children[i], delta);
	}

	root->Update(delta);
}

void RocketBall::DebugDrawChildren(GameNode* root)
{
	std::vector<GameNode*> children = *root->GetChildren();

	for (int i = 0; i < children.size(); i++)
	{
		DebugDrawChildren(children[i]);
	}

	root->DebugDraw(lines);
}

std::vector<CollisionShape*> RocketBall::GetShapesFromChildren(GameNode* root)
{
	std::vector<GameNode*> children = *root->GetChildren();

	std::vector<CollisionShape*> shapes;

	for (int i = 0; i < children.size(); i++)
	{
		std::vector<CollisionShape*> childShapes = GetShapesFromChildren(children[i]);
		shapes.insert(shapes.end(), childShapes.begin(), childShapes.end());
	}

	CollisionShape* rootShape = dynamic_cast<CollisionShape*>(root);
	if (rootShape != nullptr)
	{
		shapes.push_back(rootShape);
	}

	return shapes;
}
