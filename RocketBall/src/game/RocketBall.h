#pragma once

#include <vector>

#include "Application.h"
#include "GameThing.h"

class RocketBall : public Application
{
private:

	std::vector<GameThing> gameThings;

public:

	RocketBall();

	void Update(float delta) override;

	void OnLeftClick() override;
};