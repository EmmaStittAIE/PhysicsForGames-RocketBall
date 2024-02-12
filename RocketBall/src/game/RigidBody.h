#pragma once

#include "GameNode.h"
#include "PhysicsConsts.h"

// Temporarily built-in circle collider
class RigidBody : public GameNode
{
private:
	// Circle collider stuff
	float m_radius;

	// Rigidbody stuff
	Vec2 m_velocity;
	Vec2 m_acceleration;

	// Impulses applied externally
	//Vec2 m_impulse;
	// Force applied externally
	Vec2 m_force;

	float m_mass;

public:
	bool m_useGrav;

	RigidBody(Vec2 position, float mass, float radius, bool useGrav = true)
		: GameNode(position), m_mass(mass), m_radius(radius), m_useGrav(useGrav), m_velocity(0, 0), m_acceleration(0, 0), m_force(0, 0) {}

	void Update(float delta) override;

	void DebugDraw(LineRenderer* lines) override;

	void CursorHoldEvent(Vec2 cursorPos) override;

	void ApplyImpulse(Vec2 impulse);

	void ApplyForce(Vec2 force);
};