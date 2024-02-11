#pragma once

#include "GameNode.h"

// Temporarily built-in circle collider
class RigidBody : GameNode
{
private:
	// circle collider stuff
	float m_radius;

	// rigidbody stuff
	float m_mass;

	Vec2 m_velocity;
	Vec2 m_acceleration;

	// impulses applied externally
	//Vec2 m_impulse;
	// force applied externally
	Vec2 m_force;

public:
	RigidBody(Vec2 pos, float mass, float rad)
		: GameNode(pos), m_mass(mass), m_radius(rad), m_velocity(0, 0), m_acceleration(0, 0) {}

	void ApplyImpulse(Vec2 impulse);

	void ApplyForce(Vec2 force);
};