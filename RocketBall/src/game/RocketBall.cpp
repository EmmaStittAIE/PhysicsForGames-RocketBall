#include <iostream>

#include "RocketBall.h"

RocketBall::RocketBall()
{
	gameThings.push_back(GameNode(Vec2(0, 0)));
}

void RocketBall::Update(float delta)
{
	for (int i = 0; i < gameThings.size(); i++)
	{
		gameThings[i].Update(delta);
	}

	for (int i = 0; i < gameThings.size(); i++)
	{
		gameThings[i].DebugDraw(lines);
	}
}

void RocketBall::OnLeftClick()
{
	std::cout << "Wow a click!\n";
}