#include "RigidBody.h"

void RigidBody::ApplyImpulse(Vec2 impulse)
{
	m_velocity += impulse / m_mass;
}

void RigidBody::ApplyForce(Vec2 force)
{
	m_force += force;
}
