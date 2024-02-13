#include "RigidBody.h"

void RigidBody::Update(float delta)
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

void RigidBody::ApplyImpulse(Vec2 impulse)
{
	m_velocity += impulse / m_mass;
}

void RigidBody::ApplyForce(Vec2 force)
{
	m_netForce += force;
}

void RigidBody::SetVelocity(Vec2 velocity)
{
	m_velocity = velocity;
}
