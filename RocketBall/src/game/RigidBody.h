#pragma once

#include "GameNode.h"
#include "PhysicsConsts.h"

class RigidBody : public GameNode
{
protected:
	Vec2 m_velocity;
	Vec2 m_acceleration;

	Vec2 m_netForce;

	float m_mass;

	bool m_useGrav;

public:
	RigidBody(float xPos, float yPos, float mass, bool useGrav = true, GameNode* parent = nullptr)
		: GameNode(xPos, yPos, parent), m_mass(mass), m_useGrav(useGrav), m_velocity(0, 0), m_acceleration(0, 0), m_netForce(0, 0) {}
	RigidBody(Vec2 position, float mass, bool useGrav = true, GameNode* parent = nullptr)
		: GameNode(position, parent), m_mass(mass), m_useGrav(useGrav), m_velocity(0, 0), m_acceleration(0, 0), m_netForce(0, 0) {}

	void Update(float delta) override;

	void ApplyImpulse(Vec2 impulse);

	void ApplyForce(Vec2 force);

	void SetVelocity(Vec2 velocity);
};