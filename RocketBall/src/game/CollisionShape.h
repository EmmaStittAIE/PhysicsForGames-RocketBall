#pragma once

#include "TransformNode.h"

class PhysicsBody;
class CollisionInfo;

enum ShapeType
{
	circle,
	box,
	plane
};

class CollisionShape : public TransformNode
{
protected:
	// If not null, move this instead of children
	PhysicsBody* m_parentPB;

	CollisionShape(float xPos, float yPos, ShapeType shapeType, Vec3 debugColour = { 1, 1, 1 })
		: TransformNode(xPos, yPos, debugColour), m_parentPB(nullptr), m_shapeType(shapeType) {};
	CollisionShape(Vec2 pos, ShapeType shapeType, Vec3 debugColour = { 1, 1, 1 })
		: TransformNode(pos, debugColour), m_parentPB(nullptr), m_shapeType(shapeType) {};

public:
	ShapeType m_shapeType;

	virtual CollisionInfo CollideWithShape(CollisionShape* other) = 0;
	void ResolveCollision(CollisionInfo collision);

	void SetParentPB(PhysicsBody* physicsBody);
	PhysicsBody* GetParentPB();
	// Only used by physics body. I don't really know how to resolve this other than telling you not to use this, please
	void RemoveParentPB();
};