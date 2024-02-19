#pragma once

#include <vector>

#include "TransformNode.h"
#include "CollisionShape.h"

class PhysicsBody : public TransformNode
{
private:
	std::vector<CollisionShape*> m_collisionShapes;

	Vec2 m_velocity;
	Vec2 m_acceleration;

	Vec2 m_netForce;

	float m_mass;

public:
	bool m_isKinematic;
	bool m_useGrav;

	PhysicsBody(float xPos, float yPos, float mass, bool kinematic = false, bool useGrav = true, Vec3 debugColour = { 1, 1, 1 })
		: TransformNode(xPos, yPos, debugColour), m_mass(mass), m_isKinematic(kinematic), m_useGrav(useGrav), m_velocity(0, 0), m_acceleration(0, 0), m_netForce(0, 0) {}
	PhysicsBody(Vec2 position, float mass, bool kinematic = false, bool useGrav = true, Vec3 debugColour = { 1, 1, 1 })
		: TransformNode(position, debugColour), m_mass(mass), m_isKinematic(kinematic), m_useGrav(useGrav), m_velocity(0, 0), m_acceleration(0, 0), m_netForce(0, 0) {}

	void Update(float delta) override;
	void DebugDraw(LineRenderer* lines) override;

	void AddCollisionShape(CollisionShape* shape);
	void RemoveCollisionShape(CollisionShape* shape);
	const std::vector<CollisionShape*>* GetCollisionShapes();

	void ApplyImpulse(Vec2 impulse);
	void ApplyForce(Vec2 force);

	Vec2 GetVelocity();
	void SetVelocity(Vec2 velocity);
	float GetMass();
	void SetMass(float mass);

	~PhysicsBody();
};