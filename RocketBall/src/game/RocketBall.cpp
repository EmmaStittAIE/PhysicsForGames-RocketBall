#include <iostream>

#include "RocketBall.h"
#include "CollisionBody.h"
#include "PhysicsBody.h"
#include "CollisionShape.h"
#include "CollisionCircle.h"
#include "CollisionBox.h"
#include "CollisionPlane.h"
#include "CollisionFunctions.h"
#include "CollisionInfo.h"

RocketBall::RocketBall()
	: m_rootNode()
{
	// Create GameNodes from the bottom up (this will not be needed when editing tools are added later)
	CollisionBox* collisionBox3 = new CollisionBox(0, -0, 4, 4, { 1, 0.5f, 0 });
	CollisionCircle* collisionCircle4 = new CollisionCircle(2, -2, 0.5, { 1, 0.5f, 0 });
	CollisionCircle* collisionCircle5 = new CollisionCircle(-2, -2, 0.5, { 1, 0.5f, 0 });
	CollisionCircle* collisionCircle6 = new CollisionCircle(-2, 2, 0.5, { 1, 0.5f, 0 });
	CollisionCircle* collisionCircle7 = new CollisionCircle(2, 2, 0.5, { 1, 0.5f, 0 });
	PhysicsBody* physicsBody1 = new PhysicsBody(0, 0, 10, false, false);
	physicsBody1->AddChild(collisionBox3);
	physicsBody1->AddCollisionShape(collisionBox3);
	physicsBody1->AddChild(collisionCircle4);
	physicsBody1->AddCollisionShape(collisionCircle4);
	physicsBody1->AddChild(collisionCircle5);
	physicsBody1->AddCollisionShape(collisionCircle5);
	physicsBody1->AddChild(collisionCircle6);
	physicsBody1->AddCollisionShape(collisionCircle6);
	physicsBody1->AddChild(collisionCircle7);
	physicsBody1->AddCollisionShape(collisionCircle7);

	CollisionBox* collisionBox1 = new CollisionBox(5, -1, 1, 1, { 1, 0.5f, 0 });
	PhysicsBody* physicsBody2 = new PhysicsBody(5, -1, 1, false, false);
	physicsBody2->AddChild(collisionBox1);
	physicsBody2->AddCollisionShape(collisionBox1);

	CollisionCircle* collisionCircle1 = new CollisionCircle(6, 7, 1, { 1, 0.5f, 0 });
	PhysicsBody* physicsBody3 = new PhysicsBody(6, 7, 2, false, true);
	physicsBody3->AddChild(collisionCircle1);
	physicsBody3->AddCollisionShape(collisionCircle1);


	CollisionCircle* collisionCircle2 = new CollisionCircle(-3, 4, 1, { 1, 1, 1 });

	CollisionCircle* collisionCircle3 = new CollisionCircle(-5, -7, 5, { 1, 1, 1 });

	CollisionBox* collisionBox2 = new CollisionBox(0, -11, 10, 2, { 1, 1, 1 });

	CollisionPlane* collisionPlane1 = new CollisionPlane(0, -15, 0, { 1, 1, 1 });

	m_rootNode.AddChild(physicsBody1);
	m_rootNode.AddChild(physicsBody2);
	m_rootNode.AddChild(physicsBody3);
	m_rootNode.AddChild(collisionCircle2);
	m_rootNode.AddChild(collisionCircle3);
	m_rootNode.AddChild(collisionBox2);
	m_rootNode.AddChild(collisionPlane1);

	// Get shapes from m_gameNodes
	m_collisionBodies = GetBodiesFromChildren(&m_rootNode);
}

void RocketBall::Update(Vec2 cameraPos, Vec2 cameraHalfExtents, float delta)
{
	// Setup
	m_collisionBodies = GetBodiesFromChildren(&m_rootNode);

	// Input
	if (m_bodyOnMouse != nullptr)
	{
		PhysicsBody* bodyOnMousePB = dynamic_cast<PhysicsBody*>(m_bodyOnMouse);
		if (bodyOnMousePB != nullptr)
		{
			bodyOnMousePB->SetVelocity({ 0, 0 });
		}

		m_bodyOnMouse->SetGlobalPos(cursorPos);
	}

	if (m_bodyToFling != nullptr)
	{
		lines->SetColour({ 1, 0, 0 });
		lines->DrawLineSegment(m_bodyToFling->GetGlobalPos(), cursorPos);
	}

	// Update
	UpdateChildren(&m_rootNode, delta);

	// Collisions
	for (int repeats = 0; repeats < 10; repeats++)
	{
		std::vector<CollisionInfo> allCollisions;
		for (int i = 0; i < m_collisionBodies.size(); i++)
		{
			for (int j = i + 1; j < m_collisionBodies.size(); j++)
			{
				allCollisions.push_back(m_collisionBodies[i]->CollideWithBody(m_collisionBodies[j]));
			}
		}

		for (CollisionInfo& collision : allCollisions)
		{
			CollisionFunctions::ResolveCollision(collision);
		}
	}

	// DebugDraw
#if _DEBUG
	DebugDrawChildren(&m_rootNode, cameraPos, cameraHalfExtents);
#endif
}

void RocketBall::OnLeftClick()
{
	for (int i = 0; i < m_collisionBodies.size(); i++)
	{
		if (CollisionFunctions::DoesPointHitBody(cursorPos, m_collisionBodies[i]))
		{
			m_bodyOnMouse = m_collisionBodies[i];
		}
	}
}

void RocketBall::OnLeftRelease()
{
	m_bodyOnMouse = nullptr;
}

void RocketBall::OnRightClick()
{
	for (int i = 0; i < m_collisionBodies.size(); i++)
	{
		PhysicsBody* shapePB = dynamic_cast<PhysicsBody*>(m_collisionBodies[i]);
		if (CollisionFunctions::DoesPointHitBody(cursorPos, shapePB))
		{
			m_bodyToFling = shapePB;
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

void RocketBall::DebugDrawChildren(GameNode* root, Vec2 cameraPos, Vec2 cameraHalfExtents)
{
	std::vector<GameNode*> children = *root->GetChildren();

	for (int i = 0; i < children.size(); i++)
	{
		DebugDrawChildren(children[i], cameraPos, cameraHalfExtents);
	}

	root->DebugDraw(lines, cameraPos, cameraHalfExtents);
}

// Filters out any CollisionShapes that are assigned to a PhysicsBody
std::vector<CollisionBody*> RocketBall::GetBodiesFromChildren(GameNode* root)
{
	std::vector<GameNode*> children = *root->GetChildren();

	std::vector<CollisionBody*> bodies;

	for (int i = 0; i < children.size(); i++)
	{
		std::vector<CollisionBody*> childBodies = GetBodiesFromChildren(children[i]);
		bodies.insert(bodies.end(), childBodies.begin(), childBodies.end());
	}

	CollisionBody* rootBody = dynamic_cast<CollisionBody*>(root);
	if (rootBody != nullptr)
	{
		CollisionShape* rootShape = dynamic_cast<CollisionShape*>(root);
		if (rootShape != nullptr && rootShape->GetParentPB() != nullptr)
		{
			return bodies;
		}

		bodies.push_back(rootBody);
	}

	return bodies;
}
