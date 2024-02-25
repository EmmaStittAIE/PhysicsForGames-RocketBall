#include <sstream>

#include "PhysicsBody.h"
#include "PhysicsConsts.h"
#include "Logger.h"

void PhysicsBody::Update(float delta)
{
	if (!m_isKinematic)
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

void PhysicsBody::AddCollisionShape(CollisionShape* shape)
{
	if (shape->m_shapeType == ShapeType::plane)
	{
		Logger::LogError("Cannot use a plane as a collision shape for a RigidBody");
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

PhysicsBody::~PhysicsBody()
{
	for (int i = 0; i < m_collisionShapes.size(); i++)
	{
		delete(m_collisionShapes[i]);
	}
}
