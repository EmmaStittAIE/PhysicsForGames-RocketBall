#pragma once

#include "CollisionBody.h"

class PhysicsBody;
class CollisionInfo;

enum ShapeType
{
	circle,
	box,
	plane
};

class CollisionShape : public CollisionBody
{
protected:
	// If not null, move this instead of children
	PhysicsBody* m_parentPB = nullptr;

	CollisionShape(float xPos, float yPos, ShapeType shapeType, Vec3 debugColour = { 255, 255, 255 })
		: CollisionBody(xPos, yPos, debugColour), m_shapeType(shapeType) {};
	CollisionShape(Vec2 pos, ShapeType shapeType, Vec3 debugColour = { 255, 255, 255 })
		: CollisionBody(pos, debugColour), m_shapeType(shapeType) {};

protected:
	virtual CollisionInfo CollideWithShape(CollisionShape* other) = 0;

public:
	ShapeType m_shapeType;

	CollisionInfo CollideWithBody(CollisionBody* other) override;

	void SetParentPB(PhysicsBody* physicsBody);
	PhysicsBody* GetParentPB();
	// Only used by physics body. I don't really know how to resolve this other than telling you not to use this, please
	void RemoveParentPB();
};