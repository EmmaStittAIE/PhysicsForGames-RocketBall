#include "GameThing.h"

#include <sstream>

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

#if _DEBUG
	// Hadn't heard of this before, seems useful
	std::stringstream posString;

	posString << "Pos: (" << position.x << ", " << position.y << ")";
	lines->RenderString(posString.str(), position, 0.4);
#endif
}
