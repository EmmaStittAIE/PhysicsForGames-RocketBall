#pragma once

#include <vector>

#include "Application.h"
#include "GameNode.h"

class RocketBall : public Application
{
private:

	std::vector<GameNode> gameThings;

public:

	RocketBall();

	void Update(float delta) override;

	void OnLeftClick() override;
};