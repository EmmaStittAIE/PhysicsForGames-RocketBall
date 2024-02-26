#include <sstream>

#include "PhysicsBody.h"
#include "CollisionInfo.h"
#include "PhysicsConsts.h"
#include "Logger.h"

void PhysicsBody::Update(float delta)
{
	if (!m_kinematic)
	{
		if (m_useGrav)
		{
			ApplyForce(physics::gravity * physics::vec2Down);
		}

		// Velocity
		m_velocity += m_acceleration + (m_netForce / m_mass) * delta;

		// Position
		m_localPosition += m_velocity * delta;

		// Cleanup
		m_netForce = { 0, 0 };
	}
}

void PhysicsBody::DebugDraw(LineRenderer* lines, Vec2 cameraPos, Vec2 cameraHalfExtents)
{
	TransformNode::DebugDraw(lines, cameraPos, cameraHalfExtents);

	lines->SetColour(m_debugColour);

	if (m_velocity != Vec2{ 0, 0 })
	{
		lines->DrawLineSegment(GetGlobalPos(), GetGlobalPos() + m_velocity * 0.5f);
	}
}

CollisionInfo PhysicsBody::CollideWithBody(CollisionBody* other)
{
	CollisionInfo deepestCollision;
	for (CollisionShape* shape : m_collisionShapes)
	{
		CollisionInfo shapeCollision = shape->CollideWithBody(other);

		if (shapeCollision.penetrationDepth > deepestCollision.penetrationDepth)
		{
			deepestCollision = shapeCollision;
		}
	}

	return deepestCollision;
}

void PhysicsBody::AddCollisionShape(CollisionShape* shape)
{
	if (!m_kinematic && shape->m_shapeType == ShapeType::plane)
	{
		Logger::LogError("Cannot use a plane as a collision shape for a non-kinematic RigidBody");
		return;
	}

	m_collisionShapes.push_back(shape);

	shape->SetParentPB(this);
}

void PhysicsBody::RemoveCollisionShape(CollisionShape* shape)
{
	shape->RemoveParentPB();
	
	for (int i = 0; i < m_collisionShapes.size(); i++)
	{
		if (m_collisionShapes[i] == shape)
		{
			m_collisionShapes.erase(m_collisionShapes.begin() + i);
			return;
		}
	}
}

const std::vector<CollisionShape*>* PhysicsBody::GetCollisionShapes()
{
	return &m_collisionShapes;
}

void PhysicsBody::ApplyImpulse(Vec2 impulse)
{
	m_velocity += impulse / m_mass;
}

void PhysicsBody::ApplyForce(Vec2 force)
{
	m_netForce += force;
}

Vec2 PhysicsBody::GetVelocity()
{
	return m_velocity;
}

void PhysicsBody::SetVelocity(Vec2 velocity)
{
	m_velocity = velocity;
}

float PhysicsBody::GetMass()
{
	return m_mass;
}

void PhysicsBody::SetMass(float mass)
{
	m_mass = mass;
}

bool PhysicsBody::IsKinematic()
{
	return m_kinematic;
}

void PhysicsBody::SetKinematic(bool kinematic)
{
	// A rigidbody must be kinematic to host a plane CollisionShape, so we stop the user from setting kinematic to false if that is the case
	if (!kinematic)
	{
		for (CollisionShape* shape : m_collisionShapes)
		{
			if (shape->m_shapeType == plane)
			{
				Logger::LogError("PhysicsBody with plane collision shape cannot become dynamic");
				return;
			}
		}
	}

	m_kinematic = kinematic;
}

bool PhysicsBody::UsesGravity()
{
	return m_useGrav;
}

void PhysicsBody::SetUseGravity(bool useGravity)
{
	m_useGrav = useGravity;
}
