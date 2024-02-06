#include <iostream>

#include "RocketBall.h"

RocketBall::RocketBall()
{
	gameThings.push_back(GameNode(Vec2(0, 0), 1));
}

void RocketBall::Update(float delta)
{
	for (int i = 0; i < gameThings.size(); i++)
	{
		gameThings[i].Update(delta);
	}

	for (int i = 0; i < gameThings.size(); i++)
	{
		gameThings[i].Draw(lines);
	}
}

void RocketBall::OnLeftClick()
{
	std::cout << "Wow a click!\n";
}