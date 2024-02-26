#pragma once

#include <vector>

#include "Application.h"
#include "GameNode.h"

class CollisionBody;
class PhysicsBody;

class RocketBall : public Application
{
private:
	GameNode m_rootNode;
	std::vector<CollisionBody*> m_collisionBodies;

	CollisionBody* m_bodyOnMouse = nullptr;
	PhysicsBody* m_bodyToFling = nullptr;

	float m_flingMultiplier = 5;

public:
	RocketBall();

	void Update(Vec2 cameraPos, Vec2 cameraHalfExtents, float delta) override;

	void OnLeftClick() override;
	void OnLeftRelease() override;
	void OnRightClick() override;
	void OnRightRelease() override;

	void UpdateChildren(GameNode* root, float delta);
	void DebugDrawChildren(GameNode* root, Vec2 cameraPos, Vec2 cameraHalfExtents);
	std::vector<CollisionBody*> GetBodiesFromChildren(GameNode* root);
};