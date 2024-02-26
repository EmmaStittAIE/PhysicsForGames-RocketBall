#include "CollisionShape.h"
#include "PhysicsBody.h"
#include "CollisionInfo.h"
#include "Logger.h"

CollisionInfo CollisionShape::CollideWithBody(CollisionBody* other)
{
	CollisionShape* otherShape = dynamic_cast<CollisionShape*>(other);
	if (otherShape != nullptr)
	{
		return CollideWithShape(otherShape);
	}

	PhysicsBody* otherPB = dynamic_cast<PhysicsBody*>(other);
	if (otherPB != nullptr)
	{
		return otherPB->CollideWithBody(this);
	}

	return CollisionInfo();
}

void CollisionShape::SetParentPB(PhysicsBody* physicsBody)
{
	if (m_parentPB != nullptr)
	{
		m_parentPB->RemoveCollisionShape(this);
	}

	m_parentPB = physicsBody;
}

PhysicsBody* CollisionShape::GetParentPB()
{
	return m_parentPB;
}

void CollisionShape::RemoveParentPB()
{
	m_parentPB = nullptr;
}
