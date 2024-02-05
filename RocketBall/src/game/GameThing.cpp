#include "GameThing.h"

GameThing::GameThing(Vec2 pos, float rad)
{
	position = pos;
	radius = rad;
}

void GameThing::Update(float delta)
{
	position.x += delta;
}

void GameThing::Draw(LineRenderer* lines)
{
	lines->DrawCircle(position, radius);
}
