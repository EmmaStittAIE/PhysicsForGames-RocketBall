#include <iostream>
#include <random>

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
	// Bounding planes
	CollisionPlane* rightBoundsPlane = new CollisionPlane(15, 0, 90, { 200, 0, 0 });
	CollisionPlane* leftBoundsPlane = new CollisionPlane(-15, 0, -90, { 200, 0, 0 });
	CollisionPlane* topBoundsPlane = new CollisionPlane(0, 20, 180, { 200, 0, 0 });
	CollisionPlane* bottomRightBoundsPlane = new CollisionPlane(7.5, -15, 45, { 200, 0, 0 });
	CollisionPlane* bottomLeftBoundsPlane = new CollisionPlane(-7.5, -15, -45, { 200, 0, 0 });

	// PhysicsBodies
	// TODO: apply a random impulse to these, just for fun
	CollisionCircle* pachinkoBallCollider = new CollisionCircle(-5, 18, 1, { 195, 177, 225 });
	PhysicsBody* pachinkoBall = new PhysicsBody(-5, 18, 2, false, true, { 255, 255, 255 });
	pachinkoBall->AddChild(pachinkoBallCollider);
	pachinkoBall->AddCollisionShape(pachinkoBallCollider);

	CollisionCircle* pachinkoBallCollider2 = new CollisionCircle(5, 18, 2, Vec3{ 195, 177, 225 });
	PhysicsBody* pachinkoBall2 = new PhysicsBody(5, 18, 4, false, true, { 255, 255, 255 });
	pachinkoBall2->AddChild(pachinkoBallCollider2);
	pachinkoBall2->AddCollisionShape(pachinkoBallCollider2);

	CollisionBox* pachinkoSquareCollider = new CollisionBox(10, 18, 2, 2, Vec3{ 195, 177, 225 });
	PhysicsBody* pachinkoSquare = new PhysicsBody(10, 18, 4, false, true, { 255, 255, 255 });
	pachinkoSquare->AddChild(pachinkoSquareCollider);
	pachinkoSquare->AddCollisionShape(pachinkoSquareCollider);

	CollisionBox* pachinkoRectangleCollider = new CollisionBox(-10, 18, 1, 3, Vec3{ 195, 177, 225 });
	PhysicsBody* pachinkoRectangle = new PhysicsBody(-10, 18, 3, false, true, { 255, 255, 255 });
	pachinkoRectangle->AddChild(pachinkoRectangleCollider);
	pachinkoRectangle->AddCollisionShape(pachinkoRectangleCollider);

	// Static CollisionShapes
	CollisionCircle* circlePeg1 = new CollisionCircle(12, 10, 1, { 188, 106, 60 });
	CollisionCircle* circlePeg2 = new CollisionCircle(6, 10, 1, { 188, 106, 60 });
	CollisionCircle* circlePeg3 = new CollisionCircle(0, 10, 1, { 188, 106, 60 });
	CollisionCircle* circlePeg4 = new CollisionCircle(-6, 10, 1, { 188, 106, 60 });
	CollisionCircle* circlePeg5 = new CollisionCircle(-12, 10, 1, { 188, 106, 60 });

	CollisionBox* boxPeg1 = new CollisionBox(9, 3, 2, 2, { 213,176,124 });
	CollisionBox* boxPeg2 = new CollisionBox(3, 3, 2, 2, { 213,176,124 });
	CollisionBox* boxPeg3 = new CollisionBox(-3, 3, 2, 2, { 213,176,124 });
	CollisionBox* boxPeg4 = new CollisionBox(-9, 3, 2, 2, { 213,176,124 });

	CollisionCircle* bigCirclePeg1 = new CollisionCircle(10, -5, 3, { 132, 36, 12 });
	CollisionCircle* bigCirclePeg2 = new CollisionCircle(0, -5, 3, { 132, 36, 12 });
	CollisionCircle* bigCirclePeg3 = new CollisionCircle(-10, -5, 3, { 132, 36, 12 });

	// Attach everything to the root node
	m_rootNode.AddChild(rightBoundsPlane);
	m_rootNode.AddChild(leftBoundsPlane);
	m_rootNode.AddChild(topBoundsPlane);
	m_rootNode.AddChild(bottomRightBoundsPlane);
	m_rootNode.AddChild(bottomLeftBoundsPlane);

	m_rootNode.AddChild(pachinkoBall);
	m_rootNode.AddChild(pachinkoBall2);
	m_rootNode.AddChild(pachinkoSquare);
	m_rootNode.AddChild(pachinkoRectangle);

	m_rootNode.AddChild(circlePeg1);
	m_rootNode.AddChild(circlePeg2);
	m_rootNode.AddChild(circlePeg3);
	m_rootNode.AddChild(circlePeg4);
	m_rootNode.AddChild(circlePeg5);

	m_rootNode.AddChild(boxPeg1);
	m_rootNode.AddChild(boxPeg2);
	m_rootNode.AddChild(boxPeg3);
	m_rootNode.AddChild(boxPeg4);

	m_rootNode.AddChild(bigCirclePeg1);
	m_rootNode.AddChild(bigCirclePeg2);
	m_rootNode.AddChild(bigCirclePeg3);

	// Apply some impulses to the PhysicsBodies, just to make them bounce around a bit more
	pachinkoBall->ApplyImpulse(Vec2(18, 15));
	pachinkoBall2->ApplyImpulse(Vec2(-31, 24));
	pachinkoSquare->ApplyImpulse(Vec2(-22, 7));
	pachinkoRectangle->ApplyImpulse(Vec2(19, 29));

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
