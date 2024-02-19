#include "CollisionShape.h"
#include "PhysicsBody.h"
#include "CollisionInfo.h"

void CollisionShape::ResolveCollision(CollisionInfo collision)
{
	if (collision.penetrationDepth >= 0)
	{
		// Gotta be a better way of doing this...
		PhysicsBody* physBod1 = collision.shape1->m_parentPB;
		PhysicsBody* physBod2 = collision.shape2->m_parentPB;

		if (physBod1 != nullptr && physBod1->m_isKinematic == false)
		{
			if (physBod2 != nullptr && physBod2->m_isKinematic == false)
			{
				float pb1Mass = physBod1->GetMass();
				float pb2Mass = physBod2->GetMass();
				float totalMass = pb1Mass + pb2Mass;

				collision.shape1->MovePos(-collision.normal * collision.penetrationDepth * (pb1Mass / totalMass));
				collision.shape2->MovePos(collision.normal * collision.penetrationDepth * (pb2Mass / totalMass));
			}
			else
			{
				collision.shape1->MovePos(-collision.normal * collision.penetrationDepth);
			}
		}
		else
		{
			if (physBod2 != nullptr && physBod2->m_isKinematic == false)
			{
				collision.shape2->MovePos(collision.normal * collision.penetrationDepth);
			}
		}
	}
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
