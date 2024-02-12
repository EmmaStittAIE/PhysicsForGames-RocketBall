#include <iostream>

#include "RocketBall.h"

RocketBall::RocketBall()
{
	gameNodes.push_back(new Circle(0, 0, 2, 2, false));
	gameNodes.push_back(new Circle(2, 0, 1, 1, false));
	gameNodes.push_back(new Circle(-5, -12, 5, 5, false));
}

void RocketBall::Update(float delta)
{
	// Input
	if (leftMouseDown)
	{
		for (int i = 0; i < gameNodes.size(); i++)
		{
			gameNodes[i]->CursorHoldEvent(cursorPos);
		}
	}

	for (int i = 0; i < gameNodes.size(); i++)
	{
		gameNodes[i]->Update(delta);
	}

	for (int i = 0; i < gameNodes.size(); i++)
	{
		gameNodes[i]->DebugDraw(lines);
	}
}

void RocketBall::OnLeftClick()
{
	std::cout << "Wow a click!\n";
}

RocketBall::~RocketBall()
{
	for (int i = 0; i < gameNodes.size(); i++)
	{
		delete(gameNodes[i]);
	}
}
