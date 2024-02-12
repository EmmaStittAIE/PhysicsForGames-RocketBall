#pragma once

#include <vector>

#include "Application.h"
#include "GameNode.h"
#include "RigidBody.h"

class RocketBall : public Application
{
private:
	std::vector<GameNode*> gameNodes;

public:
	RocketBall();

	void Update(float delta) override;

	void OnLeftClick() override;

	~RocketBall();
};