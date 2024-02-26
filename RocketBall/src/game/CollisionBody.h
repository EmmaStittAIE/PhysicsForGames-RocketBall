#pragma once

#include "TransformNode.h"

class CollisionInfo;

class CollisionBody : public TransformNode
{
protected:
	CollisionBody(float xPos, float yPos, Vec3 debugColour = { 1, 1, 1 })
		: TransformNode(xPos, yPos, debugColour) {};
	CollisionBody(Vec2 pos, Vec3 debugColour = { 1, 1, 1 })
		: TransformNode(pos, debugColour) {};

public:
	virtual CollisionInfo CollideWithBody(CollisionBody* other) = 0;
};