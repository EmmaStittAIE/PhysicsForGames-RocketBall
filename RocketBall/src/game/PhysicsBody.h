#pragma once

#include <vector>

#include "CollisionBody.h"
#include "CollisionShape.h"

class CollisionInfo;

class PhysicsBody : public CollisionBody
{
private:
	std::vector<CollisionShape*> m_collisionShapes;

	Vec2 m_velocity{ 0, 0 };
	Vec2 m_acceleration{ 0, 0 };

	Vec2 m_netForce{ 0, 0 };

	float m_mass;

	bool m_kinematic;
	bool m_useGrav;

public:
	PhysicsBody(float xPos, float yPos, float mass, bool kinematic = false, bool useGrav = true, Vec3 debugColour = { 1, 1, 1 })
		: CollisionBody(xPos, yPos, debugColour), m_mass(mass), m_kinematic(kinematic), m_useGrav(useGrav){}
	PhysicsBody(Vec2 position, float mass, bool kinematic = false, bool useGrav = true, Vec3 debugColour = { 1, 1, 1 })
		: CollisionBody(position, debugColour), m_mass(mass), m_kinematic(kinematic), m_useGrav(useGrav) {}

	void Update(float delta) override;
	void DebugDraw(LineRenderer* lines, Vec2 cameraPos, Vec2 cameraHalfExtents) override;

	CollisionInfo CollideWithBody(CollisionBody* other) override;

	void AddCollisionShape(CollisionShape* shape);
	void RemoveCollisionShape(CollisionShape* shape);
	const std::vector<CollisionShape*>* GetCollisionShapes();

	void ApplyImpulse(Vec2 impulse);
	void ApplyForce(Vec2 force);

	Vec2 GetVelocity();
	void SetVelocity(Vec2 velocity);
	float GetMass();
	void SetMass(float mass);

	bool IsKinematic();
	void SetKinematic(bool kinematic);
	bool UsesGravity();
	void SetUseGravity(bool useGravity);
};