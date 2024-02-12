#include "RigidBody.h"

void RigidBody::Update(float delta)
{
	if (m_useGrav)
	{
		ApplyForce(physics::gravity * physics::vec2Down);
	}

	// Velocity
	m_velocity += m_acceleration + (m_force / m_mass) * delta;

	// Position
	m_localPosition += m_velocity * delta;

	// Cleanup
	m_force = { 0, 0 };
}

void RigidBody::CursorHoldEvent(Vec2 cursorPos)
{
	/*Vec2 cursorDisplacement = cursorPos - m_localPosition;
	if (glm::length(cursorDisplacement) <= m_radius)
	{
		// Apply a force that is stronger the closer the cursor is to the centre of the circle
		//Vec2 inverseForce = (m_radius - glm::length(cursorDisplacement)) * glm::normalize(cursorDisplacement);
		//ApplyForce(-inverseForce * 10.0f);

		ApplyForce(glm::normalize(-cursorDisplacement) * 15.0f);
	}*/
}

void RigidBody::ApplyImpulse(Vec2 impulse)
{
	m_velocity += impulse / m_mass;
}

void RigidBody::ApplyForce(Vec2 force)
{
	m_force += force;
}
