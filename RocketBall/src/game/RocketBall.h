#pragma once

#include <vector>

#include "Application.h"
#include "Circle.h"

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